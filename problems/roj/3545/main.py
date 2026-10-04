#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 06:42
# update_at: 2026-10-02 06:42

import sys


def knapsack(budget: int, items: list[tuple[int, int]]) -> int:
    """0/1 背包：容量 budget、每件物品用一次，最大化 Σ 价格×重要度。"""
    dp = [0] * (budget + 1)  # dp[c] = 花费不超过 c 时的最大乘积和
    for v, p in items:
        gain = v * p
        # 倒序枚举容量，物品只能从"还没选过它的状态"转移，保证只选一次
        for c in range(budget, v - 1, -1):
            take = dp[c - v] + gain  # 选这件物品
            if take > dp[c]:
                dp[c] = take
    return dp[budget]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    budget, m = next(data), next(data)  # 总钱数 N、物品个数 m
    items = [(next(data), next(data)) for _ in range(m)]  # (价格, 重要度)
    print(knapsack(budget, items))


if __name__ == "__main__":
    solve()
