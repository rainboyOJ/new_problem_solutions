"""Camoufox 自动登录 VJudge，然后交出 cookie。

为什么必须是 Camoufox：playwright 自带的 Chromium 一提交登录就被服务端判
``human_verification_failed``（自动化构建的指纹）；真实 chromium 也一样要人点。
Camoufox 是打了补丁的 Firefox（带指纹伪装、``navigator.webdriver=false``），实测：

1. 打开 vjudge.net 首页，Cloudflare 页面级检查直接通过（不再 403 "Just a moment"）；
2. 点开登录弹窗、填账号密码、提交 → 第一次必然回 ``Human verification failed.``，
   这是站点要渲染 Turnstile 的信号；
3. Turnstile 小组件随后**静默**返回 token（实测 3–6 秒，不需要点勾选框）；
4. 带 token 再提交一次 → ``checkLogInStatus`` 变成 true，拿到
   ``JSESSIONID`` / ``JSESSlONID`` / ``JSESSIONlD`` / ``cf_clearance``。

camoufox 是可选依赖：本模块既可以进程内 import 使用，也可以被
``vjudge_browser_login`` 用另一个解释器 ``python -m fetchers.vjudge_camoufox_login``
调起来（venv 里装了 camoufox、主进程没有的情况）。因此这里只用标准库，
相对导入一律不用。
"""

from __future__ import annotations

import json
import sys
import time
from pathlib import Path

HOME_URL = "https://vjudge.net/"
STATUS_URL = "https://vjudge.net/user/checkLogInStatus"
LOGIN_NAV_SELECTOR = "a.nav-link.login"
PROFILE_DIR = Path.home() / ".cache" / "rbook" / "vjudge-camoufox"

POLL_SECONDS = 1.5
TOKEN_SELECTOR_JS = """(() => {
  const box = document.querySelector('#turnstile-container-login');
  const input = box ? box.querySelector('input[name="cf-turnstile-response"]') : null;
  return input ? (input.value || '') : '';
})()"""


def cookie_string(context, origin: str = "https://vjudge.net") -> str:
    """把浏览器里 vjudge 的 cookie 拼成 ``a=1; b=2``。"""

    pairs: list[str] = []
    for cookie in context.cookies(origin):
        name = cookie.get("name") or ""
        value = cookie.get("value") or ""
        domain = cookie.get("domain") or ""
        if not name or not value or "vjudge" not in domain:
            continue
        pairs.append(f"{name}={value}")
    return "; ".join(pairs)


def _logged_in(context) -> bool:
    try:
        response = context.request.post(STATUS_URL, timeout=20000)
    except Exception:  # noqa: BLE001 - 浏览器网络抖动就当作还没登录
        return False
    return response.ok and "true" in response.text().lower()


def login(
    *,
    username: str,
    password: str,
    timeout: float = 180.0,
    profile_dir: Path = PROFILE_DIR,
    log=None,
) -> str:
    """自动登录 VJudge，返回 cookie 字符串；失败抛 RuntimeError。"""

    log = log or (lambda message: print(message, file=sys.stderr, flush=True))
    if not username or not password:
        raise RuntimeError("缺少 VJudge 账号密码，无法自动登录")

    try:
        from camoufox import DefaultAddons
        from camoufox.sync_api import Camoufox
    except ImportError as exc:  # pragma: no cover - 环境缺依赖
        raise RuntimeError("当前解释器没有 camoufox") from exc

    profile_dir.mkdir(parents=True, exist_ok=True)
    options = dict(
        headless=False,
        os="linux",
        humanize=True,
        # Turnstile 的勾选框在跨域 iframe 里，需要关掉 COOP 才能点/交互。
        disable_coop=True,
        i_know_what_im_doing=True,
        persistent_context=True,
        user_data_dir=str(profile_dir),
        window=(1000, 880),
    )
    try:
        options["exclude_addons"] = [DefaultAddons.UBO]
    except Exception:  # noqa: BLE001 - 老版本没有 DefaultAddons
        pass

    with Camoufox(**options) as context:
        if _logged_in(context):
            log(f"VJudge 浏览器 profile 已有登录态，直接复用：{profile_dir}")
            return cookie_string(context)

        page = context.pages[0] if context.pages else context.new_page()
        page.goto(HOME_URL, wait_until="domcontentloaded", timeout=90000)
        page.wait_for_selector("#login-username", state="attached", timeout=30000)
        page.click(LOGIN_NAV_SELECTOR)
        page.wait_for_selector("#login-password", state="visible", timeout=20000)
        page.fill("#login-username", username)
        page.fill("#login-password", password)
        page.click("#btn-login")
        log("已提交 VJudge 登录，等 Turnstile 放行…")

        deadline = time.monotonic() + timeout
        resubmitted = False
        while time.monotonic() < deadline:
            time.sleep(POLL_SECONDS)
            if _logged_in(context):
                cookie = cookie_string(context)
                log("VJudge 自动登录成功。")
                return cookie
            token = page.evaluate(TOKEN_SELECTOR_JS) or ""
            if token and not resubmitted:
                # 第一次提交是“触发 Turnstile”的代价，拿到 token 后要再提交一次。
                resubmitted = True
                log("Turnstile 已放行，重新提交登录。")
                try:
                    page.click("#btn-login", timeout=5000)
                except Exception as exc:  # noqa: BLE001 - 弹窗可能已被关闭
                    log(f"重新提交失败：{str(exc).splitlines()[0][:80]}")
        raise RuntimeError(f"VJudge 自动登录超时（{timeout:.0f}s）")


def main() -> int:
    """从 stdin 读 JSON 参数，把结果以 JSON 打到 stdout（供外部解释器调用）。"""

    try:
        payload = json.load(sys.stdin)
    except json.JSONDecodeError as exc:
        print(json.dumps({"error": f"参数不是合法 JSON：{exc}"}), flush=True)
        return 2
    try:
        cookie = login(
            username=str(payload.get("username") or ""),
            password=str(payload.get("password") or ""),
            timeout=float(payload.get("timeout") or 180.0),
            profile_dir=Path(payload.get("profile_dir") or PROFILE_DIR),
        )
    except Exception as exc:  # noqa: BLE001 - 把失败原因原样交给上层
        print(json.dumps({"error": str(exc)}, ensure_ascii=False), flush=True)
        return 1
    print(json.dumps({"cookie": cookie}, ensure_ascii=False), flush=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
