"""VJudge 浏览器登录：自动优先（Camoufox），人工兜底（playwright Chromium）。

背景：VJudge 的账号密码接口要 Cloudflare Turnstile 的 token，纯 HTTP 客户端拿不到，
服务端会回 ``user.error.human_verification_failed``。两条可行路线：

1. **Camoufox（自动）**：打了补丁的 Firefox，页面级 Cloudflare 检查和 Turnstile 都能过，
   实测 Turnstile 会静默发 token，于是账号密码可以在无人值守下提交成功。
   实现见 ``vjudge_camoufox_login``；它装了就用，没装就找一台装了它的解释器（见
   ``VJUDGE_CAMOUFOX_PYTHON``），两者都没有则退回第 2 条。
2. **playwright Chromium（人工兜底）**：弹一个真窗口，预填好账号密码并提交，
   Turnstile 需要人点一下；人点完脚本自动继续。这条路径在任何机器上都可用。

后端选择：``VJUDGE_BROWSER=camoufox|chromium|auto``（默认 auto = 先 camoufox）。

其它约定：

- 用**持久 profile**（``~/.cache/rbook/vjudge-camoufox`` / ``...-browser``），cookie 留在里面，
  下次可以静默取走，不必再打扰人。
- pi/agent 的 shell 常常没有图形环境（``XDG_SESSION_TYPE=tty``、无 ``DISPLAY``），
  这里会从同一用户的桌面会话进程（Hyprland / waybar 等）的 ``environ`` 里借
  ``WAYLAND_DISPLAY`` / ``DISPLAY`` / ``XDG_RUNTIME_DIR``，窗口才真的能显示。
- 登录完成与否只看 ``POST /user/checkLogInStatus`` 是否返回 ``true``，不猜 DOM。
"""

from __future__ import annotations

from contextlib import contextmanager
import json
import os
from pathlib import Path
import subprocess
import sys
import time
from typing import Callable, Iterator

from .base import FetchError

TOOLS_DIR = Path(__file__).resolve().parents[1]
PROFILE_DIR = Path.home() / ".cache" / "rbook" / "vjudge-browser"
CAMOUFOX_MODULE = "fetchers.vjudge_camoufox_login"

HOME_URL = "https://vjudge.net/"
STATUS_URL = "https://vjudge.net/user/checkLogInStatus"
LOGIN_NAV_SELECTOR = "a.nav-link.login"

POLL_SECONDS = 2.0
DEFAULT_TIMEOUT = 300.0

# 已知装了 camoufox 的解释器候选（用户自己装的 venv）。
CAMOUFOX_PYTHON_CANDIDATES = (
    Path.home() / ".local" / "share" / "rbook" / "camoufox-venv" / "bin" / "python",
)

# 打开窗口就能借用的图形会话变量。
SESSION_VARS = (
    "WAYLAND_DISPLAY",
    "DISPLAY",
    "XDG_RUNTIME_DIR",
    "XAUTHORITY",
    "XDG_SESSION_TYPE",
)
# 优先从这些桌面进程的 environ 里找会话变量。
DESKTOP_COMMS = ("hyprland", "waybar", "uwsm", "sway", "gnome-shell", "plasmashell", "kwin")

LogFn = Callable[[str], None]


def browser_login_allowed() -> bool:
    """是否允许自动弹浏览器登录。

    默认只在交互终端（``stderr`` 是 tty）下允许，避免 CI / 后台任务突然弹窗。
    ``VJUDGE_BROWSER_LOGIN=0/1`` 可以显式关掉或打开。
    """

    raw = os.environ.get("VJUDGE_BROWSER_LOGIN")
    if raw is not None:
        return raw.strip().lower() in ("1", "true", "yes", "on")
    return sys.stderr.isatty()


@contextmanager
def session_env(env: dict[str, str]) -> Iterator[None]:
    """临时把图形会话变量塞进 os.environ（浏览器子进程要继承它）。"""

    if not env:
        yield
        return
    saved = {name: os.environ.get(name) for name in env}
    os.environ.update(env)
    try:
        yield
    finally:
        for name, value in saved.items():
            if value is None:
                os.environ.pop(name, None)
            else:
                os.environ[name] = value


def _proc_environ(pid: str) -> dict[str, str]:
    try:
        raw = Path(f"/proc/{pid}/environ").read_bytes()
    except OSError:
        return {}
    found: dict[str, str] = {}
    for item in raw.split(b"\0"):
        key, sep, value = item.partition(b"=")
        if not sep:
            continue
        name = key.decode("utf-8", "replace")
        if name in SESSION_VARS:
            found[name] = value.decode("utf-8", "replace")
    return found


def _proc_comm(pid: str) -> str:
    try:
        return Path(f"/proc/{pid}/comm").read_text(encoding="utf-8", errors="replace").strip().lower()
    except OSError:
        return ""


def graphical_env() -> dict[str, str]:
    """返回可用的图形会话变量；当前进程没有就去桌面会话进程里借。"""

    env = {name: os.environ[name] for name in SESSION_VARS if os.environ.get(name)}
    if env.get("WAYLAND_DISPLAY") or env.get("DISPLAY"):
        return env

    uid = os.getuid()
    preferred: list[str] = []
    others: list[str] = []
    for entry in Path("/proc").iterdir():
        pid = entry.name
        if not pid.isdigit():
            continue
        try:
            if entry.stat().st_uid != uid:
                continue
        except OSError:
            continue
        comm = _proc_comm(pid)
        if any(name in comm for name in DESKTOP_COMMS):
            preferred.append(pid)
        else:
            others.append(pid)

    for pid in preferred + others:
        found = _proc_environ(pid)
        if found.get("WAYLAND_DISPLAY") or found.get("DISPLAY"):
            found.setdefault("XDG_RUNTIME_DIR", f"/run/user/{uid}")
            return found
    return env


def _stderr_log(message: str) -> None:
    print(message, file=sys.stderr, flush=True)


# ---------- Camoufox（自动登录） ----------


def camoufox_python() -> str | None:
    """找一个能 ``import camoufox`` 的解释器；没有就返回 None。

    当前解释器自己的 ``sys.executable`` 也算候选：系统里直接装了 camoufox 时不需要 venv。
    """

    candidates: list[str] = []
    explicit = os.environ.get("VJUDGE_CAMOUFOX_PYTHON")
    if explicit:
        candidates.append(explicit)
    candidates.append(sys.executable)
    candidates.extend(str(path) for path in CAMOUFOX_PYTHON_CANDIDATES)

    for python in candidates:
        if not Path(python).exists():
            continue
        try:
            probe = subprocess.run(
                [python, "-c", "import camoufox"],
                stdout=subprocess.DEVNULL,
                stderr=subprocess.DEVNULL,
                timeout=120,
            )
        except (OSError, subprocess.SubprocessError):
            continue
        if probe.returncode == 0:
            return python
    return None


def _camoufox_login_inprocess(
    *, username: str, password: str, timeout: float, log: LogFn
) -> str:
    from .vjudge_camoufox_login import login as camoufox_login

    return camoufox_login(username=username, password=password, timeout=timeout, log=log)


def _camoufox_login_subprocess(
    python: str, *, username: str, password: str, timeout: float, log: LogFn
) -> str:
    """用装了 camoufox 的另一个解释器跑同一个模块（凭据走 stdin，不进命令行）。"""

    env = dict(os.environ)
    env["PYTHONPATH"] = str(TOOLS_DIR)
    env.update(graphical_env())
    payload = json.dumps({"username": username, "password": password, "timeout": timeout})
    log(f"用 {python} 启动 Camoufox 自动登录…")
    try:
        completed = subprocess.run(
            [python, "-m", CAMOUFOX_MODULE],
            input=payload,
            capture_output=True,
            text=True,
            cwd=str(TOOLS_DIR),
            env=env,
            timeout=timeout + 120,
        )
    except subprocess.TimeoutExpired as exc:
        raise FetchError(f"Camoufox 自动登录超时（{timeout:.0f}s）") from exc

    stdout = (completed.stdout or "").strip().splitlines()
    result: dict = {}
    if stdout:
        try:
            result = json.loads(stdout[-1])
        except json.JSONDecodeError:
            result = {}
    if result.get("cookie"):
        for line in (completed.stderr or "").strip().splitlines():
            log(line)
        return str(result["cookie"])
    reason = result.get("error") or (completed.stderr or "").strip().splitlines()[-1:] or "未知原因"
    raise FetchError(f"Camoufox 自动登录失败：{reason}")


def camoufox_login(*, username: str, password: str, timeout: float, log: LogFn) -> str:
    """优先进程内跑；没有 camoufox 就找别的解释器跑。"""

    python = camoufox_python()
    if python is None:
        raise FetchError(
            "没有找到带 camoufox 的 Python 解释器；装法："
            "python3 -m venv --system-site-packages ~/.local/share/rbook/camoufox-venv && "
            "~/.local/share/rbook/camoufox-venv/bin/pip install camoufox && "
            f"~/.local/share/rbook/camoufox-venv/bin/python -m camoufox fetch"
            "（或用 VJUDGE_CAMOUFOX_PYTHON 指定解释器）"
        )
    try:
        import camoufox  # noqa: F401
    except ImportError:
        return _camoufox_login_subprocess(
            python, username=username, password=password, timeout=timeout, log=log
        )
    with session_env(graphical_env()):
        return _camoufox_login_inprocess(
            username=username, password=password, timeout=timeout, log=log
        )


# ---------- playwright Chromium（人工兜底） ----------


def _login_done(request) -> bool:
    try:
        response = request.post(STATUS_URL, timeout=15000)
    except Exception:  # noqa: BLE001 - 浏览器网络抖动就当作还没登录
        return False
    return response.ok and "true" in response.text().lower()


def cookie_string(context, origin: str = "https://vjudge.net") -> str:
    """把浏览器里 vjudge 的 cookie 拼成 ``a=1; b=2`` 形式。"""

    pairs: list[str] = []
    for cookie in context.cookies(origin):
        domain = cookie.get("domain") or ""
        name = cookie.get("name") or ""
        value = cookie.get("value") or ""
        if not name or not value or "vjudge" not in domain:
            continue
        pairs.append(f"{name}={value}")
    return "; ".join(pairs)


def chromium_login(
    *,
    username: str = "",
    password: str = "",
    timeout: float = DEFAULT_TIMEOUT,
    log: LogFn | None = None,
) -> str:
    """弹 playwright Chromium：能自动填表就先填，Turnstile 交给人点。"""

    log = log or _stderr_log
    try:
        from playwright.sync_api import sync_playwright
    except ImportError as exc:  # pragma: no cover - 环境缺依赖时的兜底
        raise FetchError(
            "浏览器登录需要 playwright：pip install playwright && playwright install chromium"
        ) from exc

    env = graphical_env()
    if not (env.get("WAYLAND_DISPLAY") or env.get("DISPLAY")):
        raise FetchError(
            "当前没有图形会话（DISPLAY / WAYLAND_DISPLAY 都取不到），无法打开 VJudge 登录窗口。"
        )

    PROFILE_DIR.mkdir(parents=True, exist_ok=True)
    with session_env(env), sync_playwright() as playwright:
        try:
            context = playwright.chromium.launch_persistent_context(
                user_data_dir=str(PROFILE_DIR),
                headless=False,
                locale="zh-CN",
                args=["--window-size=1000,860"],
            )
        except Exception as exc:  # noqa: BLE001 - playwright 的异常类型不固定
            raise FetchError(
                f"无法启动 chromium 登录窗口：{exc}"
                f"（若提示 profile 被占用，删掉 {PROFILE_DIR} 后重试）"
            ) from exc

        try:
            if _login_done(context.request):
                log(f"VJudge 浏览器 profile 里已有有效登录态，直接复用：{PROFILE_DIR}")
                return cookie_string(context)

            page = context.pages[0] if context.pages else context.new_page()
            page.goto(HOME_URL, wait_until="load", timeout=60000)
            try:
                page.click(LOGIN_NAV_SELECTOR, timeout=5000)
                page.wait_for_selector("#login-username", timeout=5000)
            except Exception:  # noqa: BLE001 - 弹窗结构变化不算致命，用户仍可手动登录
                log("自动打开登录弹窗失败，请手动点击页面右上角「登录」。")

            if username and password:
                try:
                    page.fill("#login-username", username)
                    page.fill("#login-password", password)
                    page.click("#btn-login")
                    log("已自动填入账号密码并提交；若出现人机验证，请在窗口里点一下。")
                except Exception as exc:  # noqa: BLE001 - 填不上就把窗口交给用户
                    log(f"自动填表失败（{str(exc).splitlines()[0][:60]}），请手动登录。")

            log(
                "已打开 Chromium 登录窗口，请在里面完成 vjudge.net 登录"
                "（人机验证由你完成），登录成功后会自动继续，最多等 "
                f"{timeout:.0f} 秒。"
            )
            deadline = time.monotonic() + timeout
            while time.monotonic() < deadline:
                if _login_done(context.request):
                    cookie = cookie_string(context)
                    log("VJudge 登录成功，已取到 cookie。")
                    return cookie
                time.sleep(POLL_SECONDS)
            raise FetchError(f"等待 VJudge 浏览器登录超时（{timeout:.0f}s），窗口已关闭。")
        finally:
            context.close()


# ---------- 对外入口 ----------


def browser_login(
    *,
    reason: str = "",
    username: str = "",
    password: str = "",
    timeout: float = DEFAULT_TIMEOUT,
    log: LogFn | None = None,
) -> str:
    """拿到 VJudge cookie：默认先试 Camoufox 自动登录，失败再弹 Chromium 人工登录。"""

    log = log or _stderr_log
    if reason:
        log(f"VJudge 需要登录：{reason}")

    backend = (os.environ.get("VJUDGE_BROWSER") or "auto").strip().lower()
    if backend not in ("auto", "camoufox", "chromium"):
        raise FetchError(f"未知的 VJUDGE_BROWSER={backend}（可选 auto / camoufox / chromium）")

    if backend in ("auto", "camoufox") and username and password:
        try:
            cookie = camoufox_login(
                username=username, password=password, timeout=timeout, log=log
            )
            if cookie:
                return cookie
        except FetchError as exc:
            if backend == "camoufox":
                raise
            log(f"Camoufox 自动登录没成功（{exc}），回退到人工登录窗口。")

    return chromium_login(username=username, password=password, timeout=timeout, log=log)
