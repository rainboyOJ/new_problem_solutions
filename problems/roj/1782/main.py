#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 02:20
# update_at: 2026-10-08 02:20

import sys
from itertools import islice

MOD = 998244353  # 方案数模数；与奇偶性所在的 GF(2) 运算互不干涉


def step_layer(dp: list[int], rows: list[int], cols: list[int]) -> list[int]:
    """把本层的奇偶向量 DP 推到下一层：每个状态沿"不取反(乘 A)/取反(乘 A^T)"分两路。

    rows[j] 是第 i 层到第 i+1 层邻接矩阵 A 的第 j 行掩码，cols[j] 是它的第 j 列掩码
    （即 A^T 的第 j 行掩码）。遍历位向量 v 时 v*A = XOR_{j∈v} rows[j]，
    v*A^T = XOR_{j∈v} cols[j]，两张表用逐位倍增在 O(2^k) 内建好，此后每个状态 O(1)。
    """
    size = len(dp)
    go_no, go_yes = [0], [0]
    for j in range(len(rows)):
        go_no += [x ^ rows[j] for x in go_no]  # 低 j 位的旧表复制一份再异或第 j 行
        go_yes += [x ^ cols[j] for x in go_yes]

    nxt = [0] * size
    for v in range(size):
        ways = dp[v]
        if ways:  # 不取反与取反是两种决策，两条后继都要累加，出循环后统一取模
            nxt[go_no[v]] += ways
            nxt[go_yes[v]] += ways
    return [x % MOD for x in nxt]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    m, k = next(data), next(data)
    size = 1 << k  # 奇偶向量状态数：k<=10 时最多 1024

    # 首行：源点到第 2 层各点的边，直接给出第 2 层的奇偶向量
    start = sum(bit << t for t, bit in enumerate(islice(data, k)))
    order = k * k  # 中段每行的边数：第 (j-1)*k+t 个数表示 (i,j)->(i+1,t)

    dp = [0] * size
    dp[start] = 1  # 尚未做任何取反决策，方案数 1

    # 中段 (m-3) 个层间可以取反，逐层转移
    for _ in range(m - 3):
        bits = list(islice(data, order))
        rows = [sum(bits[j * k + t] << t for t in range(k)) for j in range(k)]
        cols = [sum(bits[j * k + t] << j for j in range(k)) for t in range(k)]
        dp = step_layer(dp, rows, cols)

    # 末行：第 m-1 层各点到汇点的边，这一段不允许取反
    end = sum(bit << t for t, bit in enumerate(islice(data, k)))

    # 路径总数 mod 2 = 末层奇偶向量与汇点边掩码交集的 popcount mod 2，为 0（偶数条）才算答案
    print(sum(ways for s, ways in enumerate(dp) if (s & end).bit_count() % 2 == 0) % MOD)


if __name__ == "__main__":
    solve()
