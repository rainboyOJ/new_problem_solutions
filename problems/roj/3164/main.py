#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 21:57
# update_at: 2026-10-01 21:57

import sys

NEG = -10**100  # 不可行状态哨兵：花比可用花瓶还多时的空方案


def suffix_best(a: list[list[int]]) -> list[list[int]]:
    """g[i][j] = 第 i..F 朵花放进花瓶 j..V 的最大美观度（后缀 DP，用于贪心还原方案）。"""
    f, v = len(a), len(a[0])
    g = [[NEG] * (v + 2) for _ in range(f + 2)]
    g[f + 1] = [0] * (v + 2)  # 没有花要放：任何花瓶区间都是 0
    for i in range(f, 0, -1):
        # 第 i 朵花放 j 时，前面还剩 i-1 朵花，所以 j 至少是 i
        for j in range(v - f + i, 0, -1):
            g[i][j] = max(a[i - 1][j - 1] + g[i + 1][j + 1], g[i][j + 1])
    return g


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    f, v = next(data), next(data)
    a = [[next(data) for _ in range(v)] for _ in range(f)]

    g = suffix_best(a)

    # 贪心还原字典序最小方案：第 i 朵花取最小的花瓶 j，
    # 使得「放 j + 后缀最优」仍等于整体最优 g[i][j]
    j = 1
    pos = []
    for i in range(1, f + 1):
        while a[i - 1][j - 1] + g[i + 1][j + 1] != g[i][j]:
            j += 1
        pos.append(j)
        j += 1

    print(g[1][1])
    print(*pos)


if __name__ == "__main__":
    solve()
