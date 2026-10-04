#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 05:52
# update_at: 2026-10-02 05:55

import sys


def lis_ends(h: list[int]) -> list[int]:
    """ends[k] = 以第 k 位结尾的最长严格上升子序列长度（O(N^2) DP）。"""
    ends: list[int] = []
    for i, x in enumerate(h):
        best = max((ends[j] for j in range(i) if h[j] < x), default=0)  # 前面能接上的最长段
        ends.append(best + 1)
    return ends


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    h = [next(data) for _ in range(n)]  # 题面的高度序列
    up = lis_ends(h)                              # 以 i 结尾的严格上升段
    down = lis_ends(h[::-1])[::-1]                # 以 i 开始的严格下降段（反转即上升）
    # 以 i 为峰：上升段和下降段各算一次 i，山峰总长 = up[i] + down[i] - 1
    print(n - max(a + b - 1 for a, b in zip(up, down)))


if __name__ == "__main__":
    solve()
