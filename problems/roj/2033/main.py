#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 04:15
# update_at: 2026-10-01 04:15

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    v, n = next(data), next(data)
    coins = [next(data) for _ in range(v)]  # v 个面值，每行一个（token 化后与排版无关）

    # 完全背包计数：外层枚举面值，保证"按面值分组"，同一面值只能被重复选用，
    # 不同面值的使用顺序不产生新方案（即有序和 → 无序组合）。
    ways = [0] * (n + 1)
    ways[0] = 1  # 金额 0：不取任何货币，恰好一种方案
    for coin in coins:
        for amount in range(coin, n + 1):
            ways[amount] += ways[amount - coin]

    print(ways[n])


if __name__ == "__main__":
    solve()
