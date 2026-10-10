#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 06:12
# update_at: 2026-10-08 06:12

import sys

MOD = 10**9 + 7


def binom(n: int, k: int) -> int:
    """C(n, k) mod MOD：逐因子乘出分子与分母，再用费马小定理求分母的逆元。"""
    k = min(k, n - k)
    num = den = 1
    for i in range(k):
        num = num * (n - i) % MOD
        den = den * (i + 1) % MOD
    return num * pow(den, MOD - 2, MOD) % MOD


def count(n: int, m: int) -> int:
    """n 点 m 边、1 -> n 最短路长度恰为 n-1 的有向图个数（含重边自环）mod MOD。"""
    if n == 1:  # 起点即终点，m 条边只能全是自环，图唯一
        return 1
    if m < n - 1:  # 凑不齐 n-1 条链边，无解
        return 0

    fact = 1
    for i in range(2, n - 1):  # (n-2)!：链上的中间点可任意排列
        fact = fact * i % MOD

    kinds = n * n - (n - 1) * (n - 2) // 2  # 允许出现的边类型数 A
    free = m - n + 1  # 去掉每条链边的 1 条之后，可自由分配的边数
    return fact * binom(kinds + free - 1, free) % MOD


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    print(count(n, m))


if __name__ == "__main__":
    solve()
