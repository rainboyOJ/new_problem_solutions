#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 17:19
# update_at: 2026-09-30 17:19

import sys
from collections.abc import Callable


def build(heights: list[int], pick: Callable[[int, int], int]) -> list[list[int]]:
    """稀疏表：st[j][i] = 区间 [i, i+2^j-1] 的极值，pick 决定取最大还是最小。"""
    size = len(heights)
    st = [heights]
    j = 1
    while (1 << j) <= size:
        prev = st[-1]
        # 两个半长 2^(j-1) 的相邻区间合并成长度 2^j 的区间
        st.append([pick(prev[i], prev[i + (1 << (j - 1))]) for i in range(size - (1 << j) + 1)])
        j += 1
    return st


def range_gap(st_max: list[list[int]], st_min: list[list[int]], left: int, right: int) -> int:
    """闭区间 [left, right] 内最高与最低身高之差。"""
    length = right - left + 1
    j = length.bit_length() - 1  # 2^j <= length < 2^(j+1)
    tail = right - (1 << j) + 1  # 两段 2^j 覆盖整个区间，允许重叠
    return max(st_max[j][left], st_max[j][tail]) - min(st_min[j][left], st_min[j][tail])


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, q = next(data), next(data)
    heights = [next(data) for _ in range(n)]  # 每行一头牛的身高
    st_max = build(heights, max)
    st_min = build(heights, min)

    out: list[str] = []
    for _ in range(q):
        left, right = next(data) - 1, next(data) - 1  # 题目 1-indexed → 0-indexed
        out.append(str(range_gap(st_max, st_min, left, right)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
