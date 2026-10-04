#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 19:17
# update_at: 2026-09-30 19:24

import sys


def row_best(row: list[int]) -> int:
    """单行取数：dp[l][r] = 剩余段为 row[l..r] 时取完该段的最高得分。"""
    m = len(row)
    dp = [[0] * m for _ in range(m)]
    for i in range(m):
        dp[i][i] = row[i] << m  # 只剩一个元素，已是第 m 轮，得分为 元素 × 2^m
    for length in range(2, m + 1):  # 剩余段按长度递推，长段只依赖短段
        for l in range(m - length + 1):
            r = l + length - 1
            pick = m - r + l  # 剩余段长 r-l+1，此前两侧共取走 m-(r-l+1) 个，本次是第 pick 轮
            # 行首或行尾二选一，取走的元素乘本轮权重 2^pick
            dp[l][r] = max(dp[l + 1][r] + (row[l] << pick), dp[l][r - 1] + (row[r] << pick))
    return dp[0][m - 1]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    # 各行取数互不影响，总分就是每行独立最优之和；答案可达 2^80 量级，Python 大整数直接存
    print(sum(row_best([next(data) for _ in range(m)]) for _ in range(n)))


if __name__ == "__main__":
    solve()
