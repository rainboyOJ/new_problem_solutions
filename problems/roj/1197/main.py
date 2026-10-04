#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 23:03
# update_at: 2026-09-29 23:03

import sys
from functools import cache

INF = 10**15  # “尚未转移”的哨兵，取远大于所有距离和上界


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    m, n = next(data), next(data)

    # dis[i]：第 i 个村到第 1 个村的距离（前缀和），村编号 1..m
    dis = [0, 0] + [0] * (m - 1)
    for i in range(2, m + 1):
        dis[i] = dis[i - 1] + next(data)

    @cache
    def cost(l: int, r: int) -> int:
        """村 l..r 共用一所小学（建在中位村 mid）时，各村到学校的距离和。"""
        mid = dis[(l + r) // 2]  # 中位村的位置
        return sum(abs(dis[v] - mid) for v in range(l, r + 1))

    # dp[j][i]：前 i 个村建 j 所小学的最小距离和；转移枚举最后一所学校负责的村区间
    dp: list[list[int]] = [[INF] * (m + 1) for _ in range(n + 1)]
    for i in range(1, m + 1):
        dp[1][i] = cost(1, i)
    for j in range(2, n + 1):
        for i in range(j, m + 1):
            dp[j][i] = min(dp[j - 1][k] + cost(k + 1, i) for k in range(j - 1, i))

    print(dp[n][m])


if __name__ == "__main__":
    solve()
