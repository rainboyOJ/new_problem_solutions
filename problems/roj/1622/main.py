#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 22:32
# update_at: 2026-09-30 22:32

import sys

MAX_V = 1_000_000


def build_sieve(limit: int) -> tuple[bytearray, list[int]]:
    """欧拉筛预处理素数表与质数判定表。"""
    is_prime = bytearray([1]) * (limit + 1)
    is_prime[0] = is_prime[1] = 0
    primes: list[int] = []
    for i in range(2, limit + 1):
        if is_prime[i]:
            primes.append(i)
        for p in primes:
            if i * p > limit:
                break
            is_prime[i * p] = 0
            if i % p == 0:
                break
    return is_prime, primes


def find_goldbach_pair(n: int, primes: list[int], is_prime: bytearray) -> tuple[int, int] | None:
    """寻找使得 n = a + b 且 b - a 最大的奇素数对 (a, b)。"""
    for p in primes:
        if p > n // 2:
            break
        if p == 2:
            continue
        q = n - p
        if is_prime[q]:
            return p, q
    return None


def solve() -> None:
    input_data = sys.stdin.buffer.read().split()
    if not input_data:
        return
    is_prime, primes = build_sieve(MAX_V)
    out: list[str] = []
    for token in input_data:
        n = int(token)
        if n == 0:
            break
        pair = find_goldbach_pair(n, primes, is_prime)
        if pair:
            a, b = pair
            out.append(f"{n} = {a} + {b}")
        else:
            out.append("Goldbach's conjecture is wrong.")
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
