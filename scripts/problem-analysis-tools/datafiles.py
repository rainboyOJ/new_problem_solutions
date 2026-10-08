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

IN_SUFFIXES = (".in",)
OUT_SUFFIXES = (".out", ".ans")


def _by_suffix(d: pathlib.Path, suffixes: tuple[str, ...]) -> list[pathlib.Path]:
    if not d.is_dir():
        return []
    return sorted(
        (p for p in d.iterdir() if p.is_file() and p.suffix.lower() in suffixes),
        key=lambda p: p.name,
    )


def find_inputs(d: pathlib.Path) -> list[pathlib.Path]:
    """返回数据目录下所有输入文件（.in / .IN / .In …），按名排序。"""
    return _by_suffix(d, IN_SUFFIXES)


def find_outputs(d: pathlib.Path) -> list[pathlib.Path]:
    """返回数据目录下所有输出文件（.out / .OUT / .ans …），按名排序。"""
    return _by_suffix(d, OUT_SUFFIXES)


def find_output_for(in_path: pathlib.Path) -> pathlib.Path | None:
    """按 stem 找 `in_path` 对应的输出文件（大小写不敏感）。找不到返回 None。"""
    d = in_path.parent
    if not d.is_dir():
        return None
    stem = in_path.stem
    for p in sorted(d.iterdir()):
        if p.is_file() and p.stem == stem and p.suffix.lower() in OUT_SUFFIXES:
            return p
    return None


def pair_points(d: pathlib.Path) -> list[tuple[pathlib.Path, pathlib.Path | None]]:
    """返回 [(输入, 输出或 None), ...]，按输入名排序。"""
    return [(i, find_output_for(i)) for i in find_inputs(d)]


def count_points(d: pathlib.Path) -> int:
    """数据点数（= 输入文件数）。"""
    return len(find_inputs(d))
