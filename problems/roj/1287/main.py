#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    grid = [[next(data) for _ in range(n)] for _ in range(n)]

    # 第一行：只能从左边来，前缀和即最小费用
    dp = [0] * n
    dp[0] = grid[0][0]
    for j in range(1, n):
        dp[j] = dp[j - 1] + grid[0][j]

    # 其余行：滚动数组，dp[j] = min(上方, 左方) + 当前格费用
    for i in range(1, n):
        row = grid[i]
        dp[0] += row[0]                       # 第一列只能从上方来
        for j in range(1, n):
            dp[j] = min(dp[j], dp[j - 1]) + row[j]

    print(dp[-1])


if __name__ == "__main__":
    solve()
