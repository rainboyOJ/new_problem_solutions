"""VJudge 题面读取客户端。

VJudge 的题目页是 SPA，原始 HTML 里没有题面；真正的数据在三个地方：

1. ``/problem/info/<OJ>-<probNum>``  匿名可取，给 pid 和英文标题。
2. ``/problem/<OJ>-<probNum>``       需要登录态，HTML 里 ``<textarea name="dataJson">``
   含 ``descBriefs``（各语言/各作者的题面版本列表）。
3. ``/problem/description/<key>``    匿名可取，给某个版本的完整正文与样例表。

登录只需要在 ``POST /user/login`` 时带上用户名密码（turnstile token 可以为空），
之后持有 ``JSESSIONID`` / ``JSESSlONID`` / ``JSESSIONlD`` 三个 cookie 即可。
未登录或 cookie 过期时题目页会 303 跳 ``/?login=1``，这是判断过期的可靠信号。
"""

from __future__ import annotations

from dataclasses import dataclass
import json
import os
from pathlib import Path
import re
import time
from http.cookiejar import CookieJar
from urllib.error import HTTPError, URLError
from urllib.parse import urlencode
from urllib.request import (
    HTTPCookieProcessor,
    HTTPRedirectHandler,
    Request,
    build_opener,
)
import http.cookiejar

from .base import FetchError

BASE_URL = "https://vjudge.net"
CONFIG_PATH = Path.home() / ".config" / "rbook" / "vjudge.json"
USER_AGENT = (
    "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 "
    "(KHTML, like Gecko) Chrome/131.0.0.0 Safari/537.36"
)
RETRY_TIMES = 3
RETRY_BACKOFF_SECONDS = 1.0
LOGIN_TIMEOUT = 45


class LoginRequired(FetchError):
    """题目页 303 跳登录，说明当前没有可用登录态。"""


@dataclass(frozen=True)
class DescBrief:
    """VJudge 上的一条题面版本。"""

    key: str
    lang: str
    author: str
    update_date: str
    official: bool
    main_official: bool
    remarks: str
    author_key: str = ""

    @classmethod
    def from_payload(cls, payload: dict) -> "DescBrief":
        return cls(
            key=str(payload.get("key") or ""),
            lang=str(payload.get("lang") or ""),
            author=str(payload.get("author") or ""),
            update_date=str(payload.get("updateDate") or ""),
            official=bool(payload.get("official")),
            main_official=bool(payload.get("mainOfficial")),
            remarks=str(payload.get("remarks") or ""),
            author_key=str(payload.get("authorKey") or ""),
        )


@dataclass(frozen=True)
class Description:
    """某个题面版本的正文。"""

    key: str
    lang: str
    trustable: bool
    sections: list[tuple[str, str]]


class _LoginRedirectHandler(HTTPRedirectHandler):
    """把 /?login=1 这类跳转识别为“需要登录”，不再盲目跟随。"""

    def redirect_request(self, req, fp, code, msg, headers, newurl):  # noqa: D102
        if "login=1" in newurl or "/user/login" in newurl:
            raise LoginRequired(f"VJudge 需要登录：{newurl}")
        return super().redirect_request(req, fp, code, msg, headers, newurl)


def load_config() -> dict[str, str]:
    """读取仓库外的本地凭据文件；环境变量优先。"""

    config: dict[str, str] = {}
    if CONFIG_PATH.exists():
        try:
            raw = json.loads(CONFIG_PATH.read_text(encoding="utf-8"))
        except (OSError, json.JSONDecodeError) as exc:
            raise FetchError(f"VJudge 凭据文件无法解析：{CONFIG_PATH}: {exc}") from exc
        if isinstance(raw, dict):
            config = {str(k): str(v) for k, v in raw.items() if isinstance(v, str)}

    env_mapping = {
        "VJUDGE_COOKIE": "cookie",
        "VJUDGE_USERNAME": "username",
        "VJUDGE_PASSWORD": "password",
    }
    for env_name, key in env_mapping.items():
        value = os.environ.get(env_name)
        if value:
            config[key] = value
    return config


def save_cookie(cookie: str) -> None:
    """把刷新后的 cookie 写回凭据文件，避免每次都重新登录。"""

    try:
        config = json.loads(CONFIG_PATH.read_text(encoding="utf-8")) if CONFIG_PATH.exists() else {}
    except (OSError, json.JSONDecodeError):
        config = {}
    if not isinstance(config, dict):
        config = {}
    config["cookie"] = cookie
    try:
        CONFIG_PATH.parent.mkdir(parents=True, exist_ok=True)
        CONFIG_PATH.write_text(json.dumps(config, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
        os.chmod(CONFIG_PATH, 0o600)
    except OSError:
        # 写回失败不影响本次抓取，cookie 已保存在内存里。
        pass


class VJudgeClient:
    """带登录态与进程内缓存的 VJudge 读取器。"""

    def __init__(self, config: dict[str, str] | None = None):
        self.config = load_config() if config is None else dict(config)
        self._jar = CookieJar()
        self._opener = build_opener(HTTPCookieProcessor(self._jar), _LoginRedirectHandler())
        self._logged_in = False
        self._desc_cache: dict[str, Description] = {}
        self._briefs_cache: dict[str, tuple[str, list[DescBrief]]] = {}
        self._info_cache: dict[str, tuple[str, str]] = {}
        self._seed_cookie()

    # ---------- cookie 管理 ----------

    def _seed_cookie(self) -> None:
        raw = self.config.get("cookie") or ""
        for name, value in parse_cookie_string(raw).items():
            self._jar.set_cookie(make_cookie("vjudge.net", name, value))

    def _export_cookie(self) -> str:
        pairs = []
        for cookie in self._jar:
            if "vjudge" in cookie.domain:
                pairs.append(f"{cookie.name}={cookie.value}")
        return "; ".join(pairs)

    # ---------- 底层请求 ----------

    def _request(
        self,
        url: str,
        *,
        data: dict[str, str] | None = None,
        timeout: int = 20,
        retry: bool = True,
    ) -> str:
        attempts = RETRY_TIMES if retry else 1
        last_error: Exception | None = None
        for attempt in range(attempts):
            try:
                body = urlencode(data).encode("utf-8") if data is not None else None
                headers = {
                    "User-Agent": USER_AGENT,
                    "Accept-Language": "zh-CN,zh;q=0.9,en;q=0.8",
                }
                if data is not None:
                    headers["Content-Type"] = "application/x-www-form-urlencoded"
                    headers["X-Requested-With"] = "XMLHttpRequest"
                request = Request(url, data=body, headers=headers)
                with self._opener.open(request, timeout=timeout) as response:
                    charset = response.headers.get_content_charset() or "utf-8"
                    return response.read().decode(charset, errors="replace")
            except LoginRequired:
                raise
            except HTTPError as exc:
                if exc.code == 404:
                    raise FetchError(f"VJudge 返回 404：{url}") from exc
                last_error = exc
            except (URLError, TimeoutError, OSError) as exc:
                # socket 读超时在 3.14 上可能直接抛 TimeoutError/OSError。
                last_error = exc
            if attempt + 1 < attempts:
                time.sleep(RETRY_BACKOFF_SECONDS * (attempt + 1))
        raise FetchError(f"VJudge 请求失败：{url}: {last_error}")

    def _login(self) -> None:
        username = self.config.get("username")
        password = self.config.get("password")
        if not username or not password:
            raise FetchError(
                f"VJudge 登录态已失效，且凭据文件里没有账号密码可用于自动刷新：{CONFIG_PATH}"
            )
        # 直接 POST /user/login 即可，无需先访问首页预热 session
        # （首页含大量外链广告脚本，容易拖到读超时）。
        payload = {"username": username, "password": password, "token": ""}
        self._request(f"{BASE_URL}/user/login", data=payload, timeout=LOGIN_TIMEOUT)
        status = self._request(
            f"{BASE_URL}/user/checkLogInStatus", data={}, timeout=LOGIN_TIMEOUT
        )
        if "true" not in status.lower():
            raise FetchError("VJudge 自动登录失败，请检查凭据文件中的账号密码。")
        self._logged_in = True
        cookie = self._export_cookie()
        if cookie:
            save_cookie(cookie)
            self.config["cookie"] = cookie

    def _ensure_login(self, problem_url: str) -> str:
        """取需要登录态的页面；cookie 失效时自动用密码刷新并重试一次。"""

        try:
            return self._request(problem_url)
        except LoginRequired:
            self._login()
            return self._request(problem_url)

    # ---------- 业务接口 ----------

    def problem_info(self, oj: str, prob_num: str) -> tuple[str, str]:
        """返回 (pid, 英文标题)。匿名可取。"""

        cache_key = f"{oj}-{prob_num}"
        if cache_key in self._info_cache:
            return self._info_cache[cache_key]
        raw = self._request(f"{BASE_URL}/problem/info/{oj}-{prob_num}")
        try:
            payload = json.loads(raw)
        except json.JSONDecodeError as exc:
            raise FetchError(f"VJudge /problem/info 响应不是 JSON：{exc}") from exc
        error = payload.get("error")
        if error:
            raise FetchError(f"VJudge 上找不到题目 {oj}-{prob_num}：{error}")
        pid = str(payload.get("pid") or "")
        title = str(payload.get("title") or "").strip()
        if not pid:
            raise FetchError(f"VJudge 上找不到题目 {oj}-{prob_num}。")
        self._info_cache[cache_key] = (pid, title)
        return pid, title

    def desc_briefs(self, oj: str, prob_num: str) -> list[DescBrief]:
        """返回该题所有题面版本（需要登录态）。"""

        cache_key = f"{oj}-{prob_num}"
        if cache_key in self._briefs_cache:
            return self._briefs_cache[cache_key][1]
        html = self._ensure_login(f"{BASE_URL}/problem/{oj}-{prob_num}")
        payload = self._extract_data_json(html, oj, prob_num)
        briefs = [DescBrief.from_payload(item) for item in (payload.get("descBriefs") or [])]
        if not briefs:
            raise FetchError(f"VJudge 题目 {oj}-{prob_num} 没有任何题面版本。")
        pid = str(payload.get("problemId") or "")
        self._briefs_cache[cache_key] = (pid, briefs)
        return briefs

    def _extract_data_json(self, html: str, oj: str, prob_num: str) -> dict:
        match = re.search(r'<textarea[^>]*name="dataJson"[^>]*>([\s\S]*?)</textarea>', html)
        if not match:
            raise FetchError(
                f"VJudge 题目页结构变化，未找到 dataJson（{oj}-{prob_num}）。"
            )
        try:
            payload = json.loads(match.group(1))
        except json.JSONDecodeError as exc:
            raise FetchError(f"VJudge dataJson 解析失败：{exc}") from exc
        if not isinstance(payload, dict):
            raise FetchError("VJudge dataJson 根节点不是对象。")
        if payload.get("crawling"):
            raise FetchError(f"VJudge 题目 {oj}-{prob_num} 仍在抓取中，暂无题面。")
        if payload.get("hasStatementAccess") is False:
            raise FetchError(f"VJudge 题目 {oj}-{prob_num} 无题面访问权限。")
        return payload

    def description(self, key: str) -> Description:
        """取某个题面版本的正文。匿名可取。"""

        if key in self._desc_cache:
            return self._desc_cache[key]
        raw = self._request(f"{BASE_URL}/problem/description/{key}")
        match = re.search(
            r'<textarea[^>]*class="data-json-container"[^>]*>([\s\S]*?)</textarea>', raw
        )
        if not match:
            raise FetchError(f"VJudge 题面正文结构变化，key={key}。")
        try:
            payload = json.loads(match.group(1))
        except json.JSONDecodeError as exc:
            raise FetchError(f"VJudge 题面正文解析失败（key={key}）：{exc}") from exc
        sections: list[tuple[str, str]] = []
        for item in payload.get("sections") or []:
            if not isinstance(item, dict):
                continue
            value = item.get("value") or {}
            content = value.get("content") if isinstance(value, dict) else ""
            sections.append((str(item.get("title") or ""), str(content or "")))
        if not sections:
            raise FetchError(f"VJudge 题面 key={key} 没有任何小节。")
        desc = Description(
            key=key,
            lang=str(payload.get("lang") or ""),
            trustable=bool(payload.get("trustable")),
            sections=sections,
        )
        self._desc_cache[key] = desc
        return desc


def parse_cookie_string(raw: str) -> dict[str, str]:
    """把 ``a=1; b=2`` 形式的 cookie 字符串拆成字典。"""

    cookies: dict[str, str] = {}
    for piece in (raw or "").split(";"):
        piece = piece.strip()
        if not piece or "=" not in piece:
            continue
        name, value = piece.split("=", 1)
        name = name.strip()
        if name:
            cookies[name] = value.strip()
    return cookies


def make_cookie(domain: str, name: str, value: str) -> http.cookiejar.Cookie:
    return http.cookiejar.Cookie(
        version=0,
        name=name,
        value=value,
        port=None,
        port_specified=False,
        domain=domain,
        domain_specified=False,
        domain_initial_dot=False,
        path="/",
        path_specified=True,
        secure=False,
        expires=None,
        discard=True,
        comment=None,
        comment_url=None,
        rest={"HttpOnly": None},
        rfc2109=False,
    )
