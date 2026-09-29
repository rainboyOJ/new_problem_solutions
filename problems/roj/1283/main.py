#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 03:15
# update_at: 2026-09-30 03:15

import sys


def strictly_rising_lengths(heights: list[int]) -> list[int]:
    """dp[i] = 以 heights[i] 结尾的最长「严格上升」子序列长度（经典 O(n^2) LIS）。"""
    dp: list[int] = []
    for i, h in enumerate(heights):
        # 前面所有比自己矮的位置都能接到 h 后面；都没有就只能自己当起点，长度 1
        dp.append(1 + max((dp[j] for j in range(i) if heights[j] < h), default=0))
    return dp


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)                                     # 景点数，2 <= n <= 1000
    heights = [next(data) for _ in range(n)]           # 按游览顺序给出的海拔

    up = strictly_rising_lengths(heights)              # up[i]：从左端走到 i 且一路向上的最多景点数
    down = strictly_rising_lengths(heights[::-1])[::-1]  # down[i]：从 i 一路向下走到右端的最多景点数
    # 反转序列后「向右下降」变成「向右上升」，同一份 DP 直接复用，结果再翻回原下标

    # 峰顶 i 在 up、down 里各被数了一次，所以以 i 为峰能浏览 up[i] + down[i] - 1 个景点
    print(max(u + d - 1 for u, d in zip(up, down)))


if __name__ == "__main__":
    solve()
