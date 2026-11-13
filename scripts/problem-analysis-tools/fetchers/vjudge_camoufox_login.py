"""Camoufox 登录 VJudge，然后交出 cookie。

为什么必须是 Camoufox：playwright 自带的 Chromium 一提交登录就被服务端判
``human_verification_failed``（自动化构建的指纹）；真实 chromium 也一样要人点。
Camoufox 是打了补丁的 Firefox（带指纹伪装、``navigator.webdriver=false``），实测：

1. 打开 ``https://vjudge.net/?login=1``，Cloudflare 页面级检查直接通过
   （不再 403 "Just a moment"），登录弹窗自动展开；
2. 填账号密码、提交 → 第一次必然回 ``Human verification failed.``，
   这是站点要渲染 Turnstile 的信号；
3. Turnstile 小组件随后**静默**返回 token（实测 3–10 秒，不需要点勾选框），
   站点自己的回调会带着 token 重新提交；
4. ``checkLogInStatus`` 变成 true，拿到 ``JSESSIONID`` / ``JSESSlONID``。

**登录成功的唯一判据是页面内 XHR**：``POST /user/checkLogInStatus`` 返回 ``true``。
不能用 playwright 的 ``context.request``——那是浏览器网络栈之外的请求，
没有指纹、没有 ``cf_clearance`` 的绑定关系，Cloudflare 直接回 403 挑战页，
于是检测永远 False、脚本空转到超时（这正是以前"卡在登录后的网页上"的原因）。
页面内 fetch 走的是真实浏览器请求，返回 200 和真实登录态；DOM 里的
``#visitor_username`` 作为兜底。

人工兜底也是同一套逻辑：窗口留着不动，人自己在里面点登录，
这个轮询一看到 true 就立刻取 cookie 返回。

camoufox 是可选依赖：本模块既可以进程内 import 使用，也可以被
``vjudge_browser_login`` 用另一个解释器 ``python -m fetchers.vjudge_camoufox_login``
调起来（venv 里装了 camoufox、主进程没有的情况）。因此这里只用标准库，
相对导入一律不用。
"""

from __future__ import annotations

import json
import re
import sys
import time
from pathlib import Path

HOME_URL = "https://vjudge.net/?login=1"
STATUS_URL = "https://vjudge.net/user/checkLogInStatus"
LOGIN_NAV_SELECTOR = "a.nav-link.login"
PROFILE_DIR = Path.home() / ".cache" / "rbook" / "vjudge-camoufox"

POLL_SECONDS = 1.5
DEFAULT_TIMEOUT = 300.0

# 页面内 XHR 打登录状态：必须带 X-Requested-With + 表单 Content-Type，
# 否则 VJudge 的前端路由会把它当普通页面请求。
STATUS_JS = """async () => {
  try {
    const r = await fetch('/user/checkLogInStatus', {
      method: 'POST',
      headers: {
        'X-Requested-With': 'XMLHttpRequest',
        'Content-Type': 'application/x-www-form-urlencoded',
      },
      body: '',
    });
    return r.status + ':' + (await r.text()).slice(0, 16);
  } catch (e) {
    return 'error:' + e;
  }
}"""

# 登录后导航栏里的隐藏输入框会填上用户名；未登录时它不存在。
VISITOR_JS = """() => {
  const el = document.querySelector('#visitor_username');
  return el ? (el.value || '') : '';
}"""

# 真正的会话 cookie 只有这两个精确名字（VJudge 登录时同时下发）。
SESSION_COOKIE_NAMES = ("JSESSIONID", "JSESSlONID")

# VJudge 还顺手种下一堆**只差一个字符**的诱饵 cookie，实测它们会让 Cloudflare
# 直接 403，把 cookie 复用到纯 HTTP 客户端时请求全废：
#   JSESSIONID   /  JSESSlONID   ← 真的，必须留
#   JSESSIONlD   （I→l）        值形如 ``213815|HUSVI...``（含 ``|``）
#   JSESSlONlD   （I→l, I→l）    值 ``1``
# 判定方式：把名字小写后把 ``l`` 折成 ``i``，凡是折叠成 ``jsessionid`` 但名字不在
# 白名单里的，一律丢掉。
SAFE_COOKIE_VALUE = re.compile(r"^[A-Za-z0-9._~+/=%-]+$")


def _is_session_lookalike(name: str) -> bool:
    """是不是伪装成会话 cookie 的诱饵（名字只差一个 ``l``）。"""

    return name.lower().replace("l", "i") == "jsessionid" and name not in SESSION_COOKIE_NAMES


def cookie_string(context, origin: str = "https://vjudge.net") -> str:
    """把浏览器里 vjudge 的 cookie 拼成 ``a=1; b=2``，并过滤掉诱饵/脏值。"""

    pairs: list[str] = []
    seen: set[str] = set()
    for cookie in context.cookies(origin):
        name = cookie.get("name") or ""
        value = cookie.get("value") or ""
        domain = cookie.get("domain") or ""
        if not name or not value or "vjudge" not in domain:
            continue
        if _is_session_lookalike(name):
            continue
        if not SAFE_COOKIE_VALUE.match(value):
            # 形如 ``213815|IWM...`` 的值，带上就被 Cloudflare 403。
            continue
        if name in seen:
            continue
        seen.add(name)
        pairs.append(f"{name}={value}")
    return "; ".join(pairs)


def _status(page) -> str:
    """页面内查一次登录状态，返回 ``200:true`` / ``200:false`` / ``403:...``。"""

    try:
        return str(page.evaluate(STATUS_JS) or "")
    except Exception:  # noqa: BLE001 - 页面正在跳转/重载时 evaluate 会失败
        return ""


def _logged_in(page) -> bool:
    """登录成功了没。优先问接口，接口答不上来再看 DOM。"""

    status = _status(page)
    if status.startswith("200:"):
        return status[4:].strip().lower().startswith("true")

    # 403 之类说明探测本身被拦，退回 DOM 判据：登录后隐藏域里会有用户名，
    # 同时导航栏的「登录」链接会消失。
    try:
        if (page.evaluate(VISITOR_JS) or "").strip():
            return True
        return page.locator(LOGIN_NAV_SELECTOR).count() == 0
    except Exception:  # noqa: BLE001 - DOM 查询失败就当作还没登录
        return False


def _open_login_modal(page, log) -> bool:
    """确保登录弹窗是展开的；返回 True 表示输入框可用。"""

    try:
        page.wait_for_selector("#login-username", state="visible", timeout=20000)
        return True
    except Exception:  # noqa: BLE001 - ?login=1 没自动展开，退回点导航栏
        pass
    try:
        page.click(LOGIN_NAV_SELECTOR, timeout=5000)
        page.wait_for_selector("#login-username", state="visible", timeout=15000)
        return True
    except Exception:  # noqa: BLE001 - 结构变了也不致命，人还能自己登
        log("没能自动展开登录弹窗，请直接在窗口里点右上角「登录」手动登录。")
        return False


def login(
    *,
    username: str,
    password: str,
    timeout: float = DEFAULT_TIMEOUT,
    profile_dir: Path = PROFILE_DIR,
    log=None,
) -> str:
    """登录 VJudge（自动填表 + 人工兜底），返回 cookie 字符串；失败抛 RuntimeError。"""

    log = log or (lambda message: print(message, file=sys.stderr, flush=True))

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
        # Turnstile 的勾选框在跨域 iframe 里，需要关掉 COOP 才能交互。
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
        page = context.pages[0] if context.pages else context.new_page()

        page.goto(HOME_URL, wait_until="domcontentloaded", timeout=90000)
        if _logged_in(page):
            log(f"VJudge 浏览器 profile 已有登录态，直接复用：{profile_dir}")
            return cookie_string(context)

        if username and password:
            if _open_login_modal(page, log):
                try:
                    page.fill("#login-username", username)
                    page.fill("#login-password", password)
                    page.click("#btn-login")
                    log("已提交 VJudge 登录，等 Turnstile 放行…")
                except Exception as exc:  # noqa: BLE001 - 填不上就把窗口交给人
                    log(f"自动填表失败（{str(exc).splitlines()[0][:60]}），请手动登录。")
        else:
            log("凭据文件里没有账号密码，请在窗口里手动登录。")

        log(
            "登录窗口已打开：自动登录会自动进行；若没成功，你可以直接在窗口里"
            f"手动登录，成功后脚本会立刻继续。最多等 {timeout:.0f} 秒。"
        )
        deadline = time.monotonic() + timeout
        while time.monotonic() < deadline:
            time.sleep(POLL_SECONDS)
            if _logged_in(page):
                cookie = cookie_string(context)
                if not cookie:
                    raise RuntimeError("登录成功但没能从浏览器取到 vjudge cookie")
                log("VJudge 登录成功，已取到 cookie。")
                return cookie
        raise RuntimeError(f"等待 VJudge 登录超时（{timeout:.0f}s），窗口已关闭。")


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
            timeout=float(payload.get("timeout") or DEFAULT_TIMEOUT),
            profile_dir=Path(payload.get("profile_dir") or PROFILE_DIR),
        )
    except Exception as exc:  # noqa: BLE001 - 把失败原因原样交给上层
        print(json.dumps({"error": str(exc)}, ensure_ascii=False), flush=True)
        return 1
    print(json.dumps({"cookie": cookie}, ensure_ascii=False), flush=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
