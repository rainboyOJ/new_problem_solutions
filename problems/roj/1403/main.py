#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 08:46
# update_at: 2026-09-30 08:46

import sys
from collections.abc import Iterator


def sieve_primes(limit: int) -> bytearray:
    """使用埃氏筛生成 [0, limit] 的素数标记表：1 表示素数，0 表示合数。"""
    is_prime = bytearray([1]) * (limit + 1)
    if limit >= 0:
        is_prime[0] = 0
    if limit >= 1:
        is_prime[1] = 0

    upper = int(limit**0.5)
    for p in range(2, upper + 1):
        if is_prime[p]:
            is_prime[p * p : limit + 1 : p] = b"\x00" * len(range(p * p, limit + 1, p))
    return is_prime


def find_twin_primes(n: int) -> Iterator[tuple[int, int]]:
    """依次产出所有两数均不超过 n 的素数对 (p, p + 2)。"""
    if n < 5:
        return
    is_prime = sieve_primes(n)
    for p in range(3, n - 1, 2):
        if is_prime[p] and is_prime[p + 2]:
            yield (p, p + 2)


def solve() -> None:
    raw = sys.stdin.read().split()
    if not raw:
        return
    n = int(raw[0])

    pairs = list(find_twin_primes(n))
    if not pairs:
        print("empty")
    else:
        print("\n".join(f"{p} {p + 2}" for p, _ in pairs))


if __name__ == "__main__":
    solve()
