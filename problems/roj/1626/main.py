#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 22:56
# update_at: 2026-09-30 22:56

import sys
from math import gcd, isqrt, lcm

LIMIT = isqrt(2 * 10**9) + 1  # b1 的上界开平方，试除分解质因数只需试到这里


def prime_sieve(limit: int) -> list[int]:
    """筛出 limit 以内的全部素数：试除分解质因数时按素数表逐个试，跳过合数。"""
    is_prime = bytearray([1]) * limit
    is_prime[0:2] = b"\x00\x00"
    for p in range(2, isqrt(limit - 1) + 1):
        if is_prime[p]:
            is_prime[p * p :: p] = bytearray(len(is_prime[p * p :: p]))
    return [p for p in range(limit) if is_prime[p]]


PRIMES = prime_sieve(LIMIT)


def divisors(n: int) -> list[int]:
    """列出 n 的全部正因数：先试除分解，再让每个素因子的幂次乘进已有因数表。"""
    divs = [1]
    for p in PRIMES:
        if p * p > n:  # 已经试到 √n，剩余部分必定是 1 或单个素因子
            break
        if n % p:
            continue
        powers = [1]
        while n % p == 0:
            n //= p
            powers.append(powers[-1] * p)  # 该素因子的 0,1,...,k 次幂
        divs = [d * k for d in divs for k in powers]
    if n > 1:  # 剩下的大素因子，每个已有因数都可以选择乘或不乘它
        divs += [d * n for d in divs]
    return divs


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    n = next(data)

    for _ in range(n):
        a0, a1, b0, b1 = next(data), next(data), next(data), next(data)

        # lcm(x, b0) = b1 推出 x | b1，枚举范围由 [1, b1] 缩到 b1 的因数表（至多千余个）
        valid = sum(gcd(x, a0) == a1 and lcm(x, b0) == b1 for x in divisors(b1))
        out.append(str(valid))

    print("\n".join(out))


if __name__ == "__main__":
    solve()
