#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 03:38
# update_at: 2026-09-30 03:38

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    limit = next(data)  # 题面的 T：可用于采药的总时间
    count = next(data)  # 题面的 M：草药株数

    # dp[j] = 限定时间 j 内能采到的最大总价值；容量维度倒序保证每株草药只用一次
    dp = [0] * (limit + 1)
    for _ in range(count):
        cost = next(data)   # 采摘这株草药需要的时间
        value = next(data)  # 这株草药的价值
        for j in range(limit, cost - 1, -1):
            dp[j] = max(dp[j], dp[j - cost] + value)

    print(dp[limit])


if __name__ == "__main__":
    solve()
