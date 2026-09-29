#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 22:10
# update_at: 2026-07-05 22:10

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)  # n 种面值，目标金额 m
    coins = [next(data) for _ in range(n)]

    # f[j] = 恰好凑出面值 j 的方案数（组合计数，不区分顺序）
    f = [1] + [0] * m              # f[0] = 1：什么都不用是一种方案
    for c in coins:                # 每种面值只处理一遍 → 同一面值不区分排列顺序
        for j in range(c, m + 1):  # 正序扫：f[j] 可多次使用面值 c（完全背包）
            f[j] += f[j - c]

    print(f[m])


if __name__ == "__main__":
    solve()
