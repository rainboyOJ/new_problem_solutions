#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys

MATCH = {"(": ")", "[": "]"}


def min_insertions_to_regular(s: str) -> int:
    """求将括号序列补全为合法括号序列（GBE）所需增加的最少字符数。"""
    n = len(s)
    if n == 0:
        return 0

    dp = [[0] * n for _ in range(n)]
    for i in range(n):
        dp[i][i] = 1

    for length in range(2, n + 1):
        for i in range(n - length + 1):
            j = i + length - 1
            cost = dp[i + 1][j - 1] if MATCH.get(s[i]) == s[j] else float("inf")
            split_cost = min(dp[i][k] + dp[k + 1][j] for k in range(i, j))
            dp[i][j] = min(cost, split_cost)

    return dp[0][n - 1]


def solve() -> None:
    lines = sys.stdin.read().split()
    s = lines[0] if lines else ""
    print(min_insertions_to_regular(s))


if __name__ == "__main__":
    solve()
