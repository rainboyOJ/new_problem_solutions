#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 02:38
# update_at: 2026-09-30 02:38

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    capacity, count = next(data), next(data)  # 题面的 M 与 N
    items = [(next(data), next(data)) for _ in range(count)]  # 每件的 (W_i, C_i)

    # dp[v] = 已处理物品中，总重量不超过 v 时的最大价值；不要求装满，故初值全 0
    dp = [0] * (capacity + 1)

    for weight, value in items:
        # 容量必须倒序扫描：读到的 dp[v - weight] 还是"没考虑本物品"的旧值，
        # 本物品至多被选一次（正序会读到本轮刚更新的值，那就成了完全背包）。
        # weight > capacity 时 range 为空，装不下的物品自动被跳过。
        for v in range(capacity, weight - 1, -1):
            dp[v] = max(dp[v], dp[v - weight] + value)

    print(dp[capacity])


if __name__ == "__main__":
    solve()
