#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-04-19 10:00
# update_at: 2026-04-19 10:00

import sys


def sieve_primes(limit: int) -> list[int]:
    """线性切片筛法产出 limit 以内的全部质数。"""
    is_prime = bytearray([1]) * (limit + 1)
    is_prime[0] = is_prime[1] = 0
    for i in range(2, int(limit**0.5) + 1):
        if is_prime[i]:
            is_prime[i * i : limit + 1 : i] = b"\x00" * len(range(i * i, limit + 1, i))
    return [i for i, p in enumerate(is_prime) if p]


def legendre_factor_count(limit: int, p: int) -> int:
    """勒让德公式计算 limit! 中质因子 p 的重数。"""
    cnt = 0
    while limit:
        cnt += limit // p
        limit //= p
    return cnt


def catalan_mod(n: int, mod: int) -> int:
    """质因数分解计算第 n 项卡特兰数 C(2n, n) / (n + 1) 对 mod 取模。"""
    primes = sieve_primes(2 * n)
    ans = 1
    for p in primes:
        exp = (
            legendre_factor_count(2 * n, p)
            - legendre_factor_count(n, p)
            - legendre_factor_count(n + 1, p)
        )
        if exp:
            ans = ans * pow(p, exp, mod) % mod
    return ans


def solve() -> None:
    tokens = sys.stdin.buffer.read().split()
    if not tokens:
        return
    n, mod = int(tokens[0]), int(tokens[1])
    print(catalan_mod(n, mod))


if __name__ == "__main__":
    solve()
