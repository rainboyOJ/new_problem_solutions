#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 03:27
# update_at: 2026-09-30 03:27

import sys


def solve() -> None:
    nums = list(map(int, sys.stdin.buffer.read().split()))
    n = nums[0]

    tri: list[list[int]] = []
    p = 1
    for i in range(1, n + 1):
        tri.append(nums[p:p + i])  # 第 i 行共 i 个数
        p += i

    dp = tri[-1][:]  # 最底层 dp 初值
    for r in range(n - 2, -1, -1):
        dp = [tri[r][j] + max(dp[j], dp[j + 1]) for j in range(r + 1)]

    print(dp[0])


if __name__ == "__main__":
    solve()
