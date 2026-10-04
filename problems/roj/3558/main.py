#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 07:37
# update_at: 2026-10-02 07:37

import sys


def row_score(row: list[int]) -> int:
    """一行取数的最大得分：dp[l][r] 表示还剩 [l,r] 未取时，这一行已拿到的最高分。

    第 k 次取的权重是 2^k；区间长 L 时已取 m-L 个，本次是第 m-L+1 次取，
    所以权重 = 2^(m-L+1) = row 元素左移 (m-r+l) 位。
    """
    m = len(row)
    dp = [[0] * m for _ in range(m)]
    for l in range(m - 1, -1, -1):
        dp[l][l] = row[l] << m  # 只剩一个时它是第 m 次被取
        for r in range(l + 1, m):
            shift = m - r + l  # 本次取数的轮次编号
            take_left = (row[l] << shift) + dp[l + 1][r]   # 取行首，剩 [l+1,r]
            take_right = (row[r] << shift) + dp[l][r - 1]   # 取行尾，剩 [l,r-1]
            dp[l][r] = max(take_left, take_right)
    return dp[0][m - 1]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    # 各行独立（每行权重序列相同），总分 = 各行最优得分之和
    total = 0
    for _ in range(n):
        row = [next(data) for _ in range(m)]
        total += row_score(row)

    print(total)


if __name__ == "__main__":
    solve()
