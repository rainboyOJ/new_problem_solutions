#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 04:05
# update_at: 2026-10-08 04:05

import sys


def sieve(n: int) -> list[int]:
    """筛出 [2, n] 内的素数：每个素数是一个互斥物品组（组内是不同的幂）。"""
    is_comp = bytearray(n + 1)
    for p in range(2, int(n ** 0.5) + 1):
        if not is_comp[p]:  # p 是素数，则它的倍数全是合数
            is_comp[p * p :: p] = b'\x01' * len(range(p * p, n + 1, p))
    return [p for p in range(2, n + 1) if not is_comp[p]]


def powers(bound: int, p: int) -> list[int]:
    """列出 p 在 [1, bound] 内的全部幂 p, p^2, ...：同组内只能选其中一个。"""
    out, q = [], p
    while q <= bound:
        out.append(q)
        q *= p
    return out


def count_orders(n: int) -> int:
    """返回幂和 ≤ n 的素数幂选取方案数，即所有可能的置换阶的个数。"""
    dp = [1] + [0] * n  # dp[j]：选出的素数幂之和恰为 j 的方案数（空集和为 0）
    for p in sieve(n):
        group = powers(n, p)
        nd = dp[:]  # 本素数的滚动数组：先继承「不选 p」
        for j, ways in enumerate(dp):
            if not ways:
                continue
            for q in group:  # 只从旧状态 dp 转移，故同一素数的两个幂不会同时被选
                if j + q > n:
                    break
                nd[j + q] += ways
        dp = nd
    return sum(dp)  # 幂和 ≤ n 的选取都合法（不足的部分用长度 1 的轮换补齐）


def solve() -> None:
    n = next(iter(map(int, sys.stdin.buffer.read().split())))
    print(count_orders(n))


if __name__ == "__main__":
    solve()
