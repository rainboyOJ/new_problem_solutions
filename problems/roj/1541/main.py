#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 17:08
# update_at: 2026-09-30 17:08

import sys
from collections.abc import Iterator


def build_st(a: list[int]) -> list[list[int]]:
    """ST 表：st[k][i] = a[i..i+2^k-1] 的最大值，由下一层两个半段合并。"""
    st = [a]
    span = 2  # 当前层区间长度
    while span <= len(a):
        prev = st[-1]
        half = span >> 1
        st.append([max(prev[i], prev[i + half]) for i in range(len(a) - span + 1)])
        span <<= 1
    return st


def solve() -> None:
    data: Iterator[int] = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    a = [next(data) for _ in range(n)]  # 题目给的是 1-based 下标

    st = build_st(a)

    # logs[x] = floor(log2(x))：由 x//2 的结果递推，避免每条询问做浮点对数
    logs = [0] * (n + 1)
    for i in range(2, n + 1):
        logs[i] = logs[i >> 1] + 1

    out: list[str] = []
    append = out.append
    for _ in range(m):
        l, r = next(data) - 1, next(data) - 1
        k = logs[r - l + 1]                       # 不超过区间长度的最大 2 的幂
        # 两段等长 2^k 允许重叠：max 重复取元素不影响结果
        append(str(max(st[k][l], st[k][r - (1 << k) + 1])))

    sys.stdout.write('\n'.join(out))


if __name__ == "__main__":
    solve()
