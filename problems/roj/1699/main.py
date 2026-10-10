#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 16:05
# update_at: 2026-10-07 16:05

import sys
from collections.abc import Iterator
from itertools import accumulate

CASE_PREFIX = "Case"  # 输出格式里的固定前缀，行号紧跟其后


def prefix_function(text: str) -> list[int]:
    """pi[i] = text[:i] 的最长真 border 长度（pi[0] = pi[1] = 0）。"""
    pi = [0] * (len(text) + 1)
    k = 0                                              # 当前已匹配上的 border 长度
    for i in range(2, len(text) + 1):
        while k > 0 and text[k] != text[i - 1]:
            k = pi[k]                                  # 失配就沿 border 链往回跳
        if text[k] == text[i - 1]:
            k += 1                                     # 接上了，border 长度加一
        pi[i] = k
    return pi


def bad_lengths(seg: str, n: int) -> Iterator[int]:
    """产出本段完全不可行的长度 m：段内所有长为 m 的子串首尾都相同。

    段 T 有长度 b 的真 border 时，T 有周期 L-b，于是长度 m = L-b+1 的每个子串
    首尾都相同；反之 m 不可行也一定对应一条 border，所以 border 链就是全部答案。
    """
    pi = prefix_function(seg)
    border = pi[-1]
    while border > 0:
        m = len(seg) - border + 1
        if m <= n:                                     # 只剩下 m <= n 个石头是有意义的
            yield m
        border = pi[border]


def ring_segments(s2: str) -> Iterator[str]:
    """把 2n 长的串按"相邻字符相同"的断点切开，产出每个极大段。"""
    start = 0
    for i in range(1, len(s2)):
        if s2[i] == s2[i - 1]:
            yield s2[start:i]
            start = i
    yield s2[start:]


def solve_case(s: str) -> str:
    """返回这组数据的答案串：第 k 位表示拿走 k 个连续石头后剩下的环能否美丽。"""
    n = len(s)
    # 差分数组：diff 前缀和的前 n 项就是 res[1..n]，
    # res[m] = "能取出合法的长度为 m 的弧"的段数，"整体 +1、坏长度扣 1" 用区间加实现。
    diff = [0] * (n + 3)
    for seg in ring_segments(s + s):
        last_m = min(len(seg), n)                      # 本段能提供的最大剩余长度
        diff[1] += 1                                   # m 不超过 last_m 时本段就取得到
        diff[last_m + 1] -= 1
        for m in bad_lengths(seg, n):
            diff[m] -= 1                               # 长度 m 在本段全部不可行
            diff[m + 1] += 1

    res = list(accumulate(diff))
    # 第 k 位对应 m = n - k，所以按 m 从大到小读出答案
    return ''.join('1' if res[m] > 0 else '0' for m in range(n, 0, -1))


def solve() -> None:
    # 每组数据一行的字符串，EOF 结束；直接按空白切分即可原样拿到每个串
    cases = sys.stdin.read().split()
    out = [f"{CASE_PREFIX} {i}: {solve_case(s)}" for i, s in enumerate(cases, 1)]
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
