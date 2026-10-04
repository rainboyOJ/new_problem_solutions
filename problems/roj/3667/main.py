#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 14:42
# update_at: 2026-10-02 14:42

import sys

NEG = -10**18  # max 扫描的初值：任何真实路径和都远大于它


def advance(dp: list[int], pre: list[int]) -> list[int]:
    """按列转移一列：由上一列每行的最优值 dp 推出本列每行的最优值。

    pre 是本列前缀和，pre[i] = 前 i 行之和（pre[0] = 0）。从进入行 r 走到离开行 c
    收集的格子是本列 [min(r,c), max(r,c)] 这一段，按 r <= c 与 r >= c 拆成两半，
    各用一次单调扫描取 max，不必两两枚举 (r, c)。
    """
    n = len(dp)
    lo: list[int] = []  # lo[c] = max_{r<=c} (dp[r] - pre[r])：进来的行在上方
    best = NEG
    for r, value in enumerate(dp):
        best = max(best, value - pre[r])
        lo.append(best)
    hi: list[int] = []  # hi[c] = max_{r>=c} (dp[r] + pre[r+1])：进来的行在下方
    best = NEG
    for r in range(n - 1, -1, -1):
        best = max(best, dp[r] + pre[r + 1])
        hi.append(best)
    hi.reverse()  # 倒着扫完再翻转，让下标对齐离开行 c
    return [max(pre[c + 1] + lo[c], hi[c] - pre[c]) for c in range(n)]


def solve() -> None:
    data = sys.stdin.buffer
    n, m = map(int, data.readline().split())

    # 按行读入、按列存前缀和：pre[j][i] = 第 j 列前 i 行之和
    pre = [[0] * (n + 1) for _ in range(m)]
    for i in range(n):
        row = list(map(int, data.readline().split()))
        for j, value in enumerate(row):
            pre[j][i + 1] = pre[j][i] + value

    dp = pre[0][1:]  # 第 1 列只能从第 1 行进入，走到第 r 行时已收集前 r 行
    for j in range(1, m):
        dp = advance(dp, pre[j])

    print(dp[-1])  # 终点固定在第 n 行、第 m 列


if __name__ == "__main__":
    solve()
