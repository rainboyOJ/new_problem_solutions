#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 15:16
# update_at: 2026-10-08 15:16

import sys

MOD = 1000000007  # 模数

# 类型别名（Python 3.12+ 的 type 语句）
type Table = list[list[int]]          # 二维 DP / 组合数表
type Grid3 = list[list[list[int]]]    # 三维 DP 表，Grid3[a][b][c] 三个下标各一层


def build_binom(n: int) -> Table:
    """C[i][j] = C(i, j) mod MOD，预处理到下标 n。"""
    c = [[0] * (n + 1) for _ in range(n + 1)]
    for i in range(n + 1):
        c[i][0] = 1
        for j in range(1, i + 1):
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD
    return c


def count_connected(n: int, binom: Table) -> list[int]:
    """conn[i] = i 个点的连通简单图数：全部图数减去 1 号点所在连通块不足 i 点的情形。"""
    total = [pow(2, i * (i - 1) // 2, MOD) for i in range(n + 1)]  # 任意简单图数
    conn = [0] * (n + 1)
    conn[1] = 1
    for i in range(2, n + 1):
        disconnected = sum(binom[i - 1][v - 1] * conn[v] * total[i - v] for v in range(1, i)) % MOD
        conn[i] = (total[i] - disconnected) % MOD
    return conn


def refresh_hang(hang: Grid3, dp: Table, binom: Table, s: int, n: int) -> None:
    """把“挂载总点数为 s”的方案并入 hang。

    挑出含最小标号点、内部恰有 c 条割边的 v 点连通块，它还要选 1 个代表点
    连向外部 k 个已存在的点（k*v 种），连边自身就是一条割边，于是割边数加一。
    """
    for v in range(1, s + 1):
        for c in range(v):
            if dp[v][c] == 0:
                continue
            blocks = binom[s - 1][v - 1] * v * dp[v][c] % MOD  # 选点并选代表点的系数
            for y_prev in range(s - v + 1):
                y = y_prev + c + 1  # 加上新挂出去的那一条割边
                for k in range(1, n + 1):
                    prev_hang = hang[k][s - v][y_prev]
                    if prev_hang:
                        hang[k][s][y] = (hang[k][s][y] + blocks * k * prev_hang) % MOD


def count_by_bridges(n: int, binom: Table, conn: list[int]) -> Table:
    """dp[s][j] = s 个点、恰好 j 条割边的连通图数；从小到大算并为下一阶段维护 hang。"""
    hang = [[[0] * (n + 1) for _ in range(n + 1)] for _ in range(n + 1)]
    for k in range(1, n + 1):
        hang[k][0][0] = 1  # 一个点都不挂时只有一种空方案
    dp = [[0] * (n + 1) for _ in range(n + 1)]
    for s in range(1, n + 1):
        if s == 1:
            dp[1][0] = 1  # 单点图没有割边
        else:
            # 根边双有 k 个点（含 1 号点），其余 s-k 个点挂上去，割边数恰为 j
            for j in range(1, s):
                dp[s][j] = sum(
                    binom[s - 1][k - 1] * dp[k][0] * hang[k][s - k][j] for k in range(1, s)
                ) % MOD
            dp[s][0] = (conn[s] - sum(dp[s][1:s])) % MOD  # 无割边 = 连通图总数 - 有割边的
        refresh_hang(hang, dp, binom, s, n)
    return dp


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    binom = build_binom(n)
    conn = count_connected(n, binom)
    dp = count_by_bridges(n, binom, conn)

    # 题目要“割边不超过 M 条”，即前缀和；n 个点最多 n-1 条割边
    bridges_at_most = min(m, n - 1)
    print(sum(dp[n][:bridges_at_most + 1]) % MOD)


if __name__ == "__main__":
    solve()
