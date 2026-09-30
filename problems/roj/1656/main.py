#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 00:21
# update_at: 2026-10-01 00:21

import sys
from itertools import accumulate

MOD = 10007  # 题面模数，恰好是素数：Lucas 定理和费马小定理都能用

# FACT[i] = i! mod MOD（只用到 i < MOD），共 MOD 项；p 进制每一数位的组合数都查它
FACT = list(accumulate(range(1, MOD), lambda acc, i: acc * i % MOD, initial=1))


def small_comb(n: int, m: int) -> int:
    """p 进制单个数位上的 C(n, m) mod p（传入的 n, m 都已小于 p）。"""
    if m > n:
        return 0  # 这一位 m 已经超过 n，整个 Lucas 乘积因子为 0
    return FACT[n] * pow(FACT[m] * FACT[n - m], -1, MOD) % MOD  # 逆元当除法


def lucas(n: int, m: int) -> int:
    """Lucas 定理：C(n, m) ≡ ∏ C(n_i, m_i) (mod p)，n_i / m_i 是 p 进制各位数字。"""
    res = 1
    while n or m:
        res = res * small_comb(n % MOD, m % MOD) % MOD
        n //= MOD
        m //= MOD
    return res


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    t = next(data)  # 询问组数
    out = [str(lucas(next(data), next(data))) for _ in range(t)]
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
