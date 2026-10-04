#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 04:05
# update_at: 2026-10-02 04:05

import sys


def knapsack(cap: int, vols: list[int]) -> list[int]:
    """0/1 背包：dp[c] = 只用已处理物品、容量 c 时能装下的最大总体积。"""
    dp = [0] * (cap + 1)
    for v in vols:
        # 倒序扫容量，保证每件物品只被选一次
        dp[v:] = map(max, dp[v:], (used + v for used in dp[:-v or None]))
    return dp


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    box_volume = next(data)  # 箱子容量 V
    n = next(data)
    vols = [next(data) for _ in range(n)]

    best = knapsack(box_volume, vols)[box_volume]
    print(box_volume - best)  # 装得越多，剩余空间越小


if __name__ == "__main__":
    solve()
