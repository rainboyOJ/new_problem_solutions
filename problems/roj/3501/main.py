#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 03:23
# update_at: 2026-10-02 03:23

import sys


def solve() -> None:
    n, k = map(int, sys.stdin.readline().split())
    s = sys.stdin.readline().strip()

    # dp[j][i]：前 i 个数字之间插 j 个乘号能得到的最大乘积
    dp: list[list[int]] = [[0] * (n + 1) for _ in range(k + 1)]
    dp[0] = [0] + [int(s[:i]) for i in range(1, n + 1)]  # 不放乘号：整个前缀自己就是一个数

    for j in range(1, k + 1):
        # 枚举最后一个乘号的位置：插在第 t 位后面，前 t 位放 j-1 个乘号，s[t:i] 自成一段
        for i in range(j + 1, n + 1):
            dp[j][i] = max(dp[j - 1][t] * int(s[t:i]) for t in range(j, i))

    print(dp[k][n])


if __name__ == "__main__":
    solve()
