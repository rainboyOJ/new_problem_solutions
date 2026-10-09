"""数据文件发现：大小写不敏感。

⚠ 为什么需要这个模块
------------------
素材数据文件名**不统一**，实测三种形态：

    problem1.in / problem1.out        ← 绝大多数
    SNOW1.IN / SNOW1.OUT              ← 5 道题（1374 1378 1384 1388 1392）
    count1.in / count1.out            ← 少数

而 Python 的 `pathlib.Path.glob("*.in")` 在 macOS/Linux 上**大小写敏感**，
于是 `glob("*.in")` 对 `SNOW1.IN` 返回**空**。

后果（2026-10-08 由 roj-verify-worker-6 在 1374 上发现）：
`check_new_analysis.py --realdata` 看到空列表后走「data/ 为空（跳过）」分支，
**静默返回通过** —— 10 个真实数据点一个都没跑，而闸门显示 ✅。
这类「静默空转」比报错危险得多：报错会有人管，空转没人管。

另有一个连带的配对错误：`Path("SNOW1.IN").with_suffix(".out")` 得到 `SNOW1.out`，
与实际文件名 `SNOW1.OUT` 不匹配。所以**输入与输出都要用本模块按 stem 配对**。

用法
----
    from datafiles import find_inputs, find_outputs, pair_points

    ins = find_inputs(data_dir)              # 大小写不敏感的 *.in
    pairs = pair_points(data_dir)            # [(in_path, out_path_or_None), ...]
"""

from __future__ import annotations

import pathlib

# ⚠ 后缀白名单必须覆盖全仓实际用到的命名。
# 2026-10-09 实测全仓数据文件后缀分布：
#   .in 14764 · .out 13378 · .ans 1246 · .txt 26 · .cpp 35 · .bat 22 · (无后缀) 17 …
# ★ `.txt` 用于 `inputN.txt` / `outputN.txt`（如 3194），**全仓唯一一种这种命名**。
#   漏掉它会让 `find_inputs` 返回空 ⇒ 闸门报「data/ 为空（跳过）」
#   ⇒ **静默空转**（T1）：闸门假装通过，实则一个点都没跑。
IN_SUFFIXES = (".in", ".txt")
# ⚠ .txt 也要出现在 OUT 白名单 —— `inputN.txt` 的配对是 `outputN.txt`（也是 .txt）
OUT_SUFFIXES = (".out", ".ans", ".txt")


# 「前缀成对」命名：`inputN.txt` ↔ `outputN.txt`（stem 不同名，无法按 stem 配对）
_PREFIX_PAIRS = (("input", "output"),)


def _prefix_counterpart_stem(stem: str) -> str | None:
    """若 `stem` 以 `input` 开头，返回对应的 `output…` stem；否则 None。"""
    low = stem.lower()
    for pre_in, pre_out in _PREFIX_PAIRS:
        if low.startswith(pre_in):
            return pre_out + stem[len(pre_in):]
    return None


def _is_data_pair(d: pathlib.Path, in_path: pathlib.Path, out_path: pathlib.Path) -> bool:
    """判断 out_path 是否为 in_path 的配对输出（stem 同名 或 inputN/outputN）。

    ⚠ 必须排除「文件自己」：`input0.txt` 的 stem 与自身相同，
      若不加这一条会把输入当成自己的输出（实测 `input0.txt → input0.txt`）。
    ⚠ `.txt` 后缀两用（`input*.txt` 是输入、`output*.txt` 是输出），
      故对 `.txt` 额外要求候选 stem 以 `output` 开头。
    """
    if out_path == in_path:
        return False
    if out_path.suffix.lower() == ".txt" and out_path.stem.lower().startswith("input"):
        return False          # input*.txt 永远是输入，不是输出
    if in_path.stem == out_path.stem:
        return True
    want = _prefix_counterpart_stem(in_path.stem)
    return bool(want) and want == out_path.stem


def _by_suffix(d: pathlib.Path, suffixes: tuple[str, ...]) -> list[pathlib.Path]:
    if not d.is_dir():
        return []
    return sorted(
        (p for p in d.iterdir() if p.is_file() and p.suffix.lower() in suffixes),
        key=lambda p: p.name,
    )


def find_inputs(d: pathlib.Path) -> list[pathlib.Path]:
    """返回数据目录下所有输入文件（.in / .IN / .In / .txt …），按名排序。

    ⚠ 若数据目录里**只有** `.txt` 而没有任何 `.in`，则只认 `input*.txt`，
    避免把无关的 `.txt`（说明/配置）当成测试点。
    """
    all_ins = _by_suffix(d, IN_SUFFIXES)
    if any(p.suffix.lower() == ".in" for p in all_ins):
        return [p for p in all_ins if p.suffix.lower() == ".in"]
    # 纯 .txt 目录：只取 input*.txt
    return [p for p in all_ins if p.stem.lower().startswith("input")]


def find_outputs(d: pathlib.Path) -> list[pathlib.Path]:
    """返回数据目录下所有输出文件（.out / .OUT / .ans …），按名排序。"""
    return _by_suffix(d, OUT_SUFFIXES)


def find_output_for(in_path: pathlib.Path) -> pathlib.Path | None:
    """按 stem 找 `in_path` 对应的输出文件（大小写不敏感）。找不到返回 None。"""
    d = in_path.parent
    if not d.is_dir():
        return None
    for p in sorted(d.iterdir()):
        if p.is_file() and p.suffix.lower() in OUT_SUFFIXES and _is_data_pair(d, in_path, p):
            return p
    return None


def pair_points(d: pathlib.Path) -> list[tuple[pathlib.Path, pathlib.Path | None]]:
    """返回 [(输入, 输出或 None), ...]，按输入名排序。"""
    return [(i, find_output_for(i)) for i in find_inputs(d)]


def count_points(d: pathlib.Path) -> int:
    """数据点数（= 输入文件数）。"""
    return len(find_inputs(d))
