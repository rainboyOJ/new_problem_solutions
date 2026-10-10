"""Special-judge（多解判定）注册表。

⚠ 为什么需要它
------------
项目闸门（`check_sample.py` / `check_new_analysis.py`）默认做**逐字节/逐 token** 比对。
但有些题的题面明写：

  > 如果答案不唯一，输出**任意一种合法方案**即可。

对这类题，逐字节比对会**把合法解判成错的** —— 这是**闸门的适用性缺陷**，不是程序缺陷。

2026-10-08 在 3072《八数码》上发现：
  · 期望 `dluldrurulldrrulldrrdllrurulddr`（31 步）
  · 程序 `dllururddlluurrddlulurrdldlurdr`（31 步）
  两者**都是合法最短解**，题面也允许任意方案 ⇒ 逐字节比对必然失败。

规模：全仓 **58 道**题的题面含「任意一种/不唯一/任一合法」等表述。
（注意：「题面说多解」≠「闸门一定错」—— 若 `.out` 恰好与常见实现一致，逐字节也能过。
  所以**需要逐题判断**，不能全盘否定。）

## 用法

在本目录（`scripts/problem-analysis-tools/spj/`）下放 `<pid>.py`，实现：

    def check(inp: str, got: str, want: str) -> tuple[bool, str]:
        '''返回 (是否通过, 说明)。inp/got/want 都是文件的**原始文本**。'''
        ...

然后 `check_sample.py --pid <pid>` 与 `check_new_analysis.py` 会自动改用该判定器；
没有对应 `<pid>.py` 时退回逐 token 比对。

## 设计约束

- **不能只信 `want`**：多解题的 `want` 只是「一个」合法答案，
  判定器必须**独立验证 `got` 的合法性**（例如模拟操作、检查约束），
  而不是「got 是否等于 want」的变体。
- **失败要给出可读理由**（供 worker 的最小复现使用）。
"""

from __future__ import annotations

import importlib.util
import pathlib
import sys

SPJ_DIR = pathlib.Path(__file__).resolve().parent / "spj"
_CACHE: dict[str, object] = {}


def available(pid: str) -> bool:
    return (SPJ_DIR / f"{pid}.py").is_file()


def load(pid: str):
    """加载 <pid>.py；不存在返回 None。"""
    if pid in _CACHE:
        return _CACHE[pid]
    path = SPJ_DIR / f"{pid}.py"
    if not path.is_file():
        _CACHE[pid] = None
        return None
    spec = importlib.util.spec_from_file_location(f"spj_{pid}", path)
    if spec is None or spec.loader is None:
        _CACHE[pid] = None
        return None
    mod = importlib.util.module_from_spec(spec)
    sys.modules[f"spj_{pid}"] = mod
    spec.loader.exec_module(mod)
    _CACHE[pid] = mod
    return mod


def check(pid: str, inp: str, got: str, want: str) -> tuple[bool, str] | None:
    """用 <pid>.py 判定。没有该题的判定器时返回 None（调用方退回逐 token 比对）。"""
    mod = load(pid)
    if mod is None:
        return None
    fn = getattr(mod, "check", None)
    if fn is None:
        return None
    try:
        ok, detail = fn(inp, got, want)
    except Exception as e:  # 判定器自身出错要让调用方看见，而不是静默判过
        return False, f"SPJ 抛异常：{type(e).__name__}: {e}"
    return bool(ok), str(detail)


def list_available() -> list[str]:
    return sorted(p.stem for p in SPJ_DIR.glob("*.py")
                  if p.stem not in ("__init__",) and not p.stem.startswith("_"))
