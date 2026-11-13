"""VJudge 浏览器登录：只用 Camoufox 一条路。

背景：VJudge 的账号密码接口要 Cloudflare Turnstile 的 token，纯 HTTP 客户端拿不到，
服务端会回 ``user.error.human_verification_failed``。唯一可行的路线是 Camoufox：
打了补丁的 Firefox，页面级 Cloudflare 检查和 Turnstile 都能过，Turnstile 会静默发
token，于是账号密码可以在无人值守下提交成功；万一 Turnstile 还是要人，同一个窗口
里人点一下也能过。实现见 ``vjudge_camoufox_login``。

（以前还有一条 playwright Chromium 人工兜底，已删除：它提交必然被判
``human_verification_failed``，而且用 ``context.request`` 探登录状态会被
Cloudflare 403，导致永远检测不到登录成功，只能空转到超时。现在只维护一份代码。）

其它约定：

- 用**持久 profile**（``~/.cache/rbook/vjudge-camoufox``），cookie 留在里面，
  下次可以静默取走，不必再打扰人。
- pi/agent 的 shell 常常没有图形环境（``XDG_SESSION_TYPE=tty``、无 ``DISPLAY``），
  这里会从同一用户的桌面会话进程（Hyprland / waybar 等）的 ``environ`` 里借
  ``WAYLAND_DISPLAY`` / ``DISPLAY`` / ``XDG_RUNTIME_DIR``，窗口才真的能显示。
- 登录完成与否只看**页面内** XHR 的 ``POST /user/checkLogInStatus`` 是否返回
  ``true``，不猜 DOM；DOM 只作为兜底。
"""

from __future__ import annotations

from contextlib import contextmanager
import json
import os
from pathlib import Path
import subprocess
import sys
from typing import Callable, Iterator

from .base import FetchError

TOOLS_DIR = Path(__file__).resolve().parents[1]
CAMOUFOX_MODULE = "fetchers.vjudge_camoufox_login"

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
    log(f"用 {python} 启动 Camoufox 登录…")
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
        raise FetchError(f"Camoufox 登录超时（{timeout:.0f}s）") from exc

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
    raise FetchError(f"Camoufox 登录失败：{reason}")


def browser_login(
    *,
    reason: str = "",
    username: str = "",
    password: str = "",
    timeout: float = DEFAULT_TIMEOUT,
    log: LogFn | None = None,
) -> str:
    """拿到 VJudge cookie：用 Camoufox 登录（有密码就自动填，没有就让人手动登）。"""

    log = log or _stderr_log
    if reason:
        log(f"VJudge 需要登录：{reason}")

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
