#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 00:22
# update_at: 2026-10-01 00:22

import sys

P = 2333  # 模数，题目给定质数


def init_tables() -> tuple[list[list[int]], list[list[int]]]:
    """预处理模 P 下的杨辉三角组合数表与行前缀和表。"""
    c = [[0] * P for _ in range(P)]
    s = [[0] * P for _ in range(P)]
    for i in range(P):
        c[i][0] = 1
        s[i][0] = 1
        for j in range(1, i + 1):
            c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % P
            s[i][j] = (s[i][j - 1] + c[i][j]) % P
        for j in range(i + 1, P):
            s[i][j] = s[i][i]
    return c, s


C, S = init_tables()


def lucas(n: int, m: int) -> int:
    """计算 Lucas 定理下的组合数 C(n, m) mod P。"""
    if m == 0:
        return 1
    if n < m:
        return 0
    if n < P and m < P:
        return C[n][m]
    return lucas(n // P, m // P) * C[n % P][m % P] % P


def query_sum(n: int, k: int) -> int:
    """计算前缀组合数和 S(n, k) = sum_{i=0}^k C(n, i) mod P。"""
    if k < 0:
        return 0
    if n < P and k < P:
        return S[n][k]
    # Lucas 递归展开：整除整块部分乘以对应前缀和 + 散块部分
    full_blocks = S[n % P][P - 1] * query_sum(n // P, k // P - 1)
    partial_block = lucas(n // P, k // P) * S[n % P][k % P]
    return (full_blocks + partial_block) % P


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)

    for _ in range(T):
        n = next(data)
        k = next(data)
        out.append(str(query_sum(n, k)))

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
