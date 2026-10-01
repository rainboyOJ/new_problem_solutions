#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 06:05
# update_at: 2026-10-02 06:05

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    T = next(data)  # 总共能用来采药的时间
    M = next(data)  # 草药数目

    # dp[t]：只用已处理过的草药、耗时不超过 t 时的最大总价值
    dp = [0] * (T + 1)
    for _ in range(M):
        cost = next(data)  # 采摘这株草药需要的时间
        value = next(data)  # 这株草药的价值
        # 倒序枚举容量：保证 dp[cap - cost] 还是“没采过这株”的旧值
        for cap in range(T, cost - 1, -1):
            dp[cap] = max(dp[cap], dp[cap - cost] + value)

    print(dp[T])


if __name__ == "__main__":
    solve()
