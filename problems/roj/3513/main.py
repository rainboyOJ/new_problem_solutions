#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 04:44
# update_at: 2026-10-02 04:44

import sys
from functools import cache
from itertools import combinations
from math import isqrt

SIEVE_LIMIT = 10**4  # 组合和 ≤ 20×5×10^6 = 10^8，试除只需到 √10^8 = 10^4


def primes_upto(limit: int) -> list[int]:
    """埃氏筛出 [2, limit] 内全部素数，判素时只试这些候选因子。"""
    sieve = bytearray([1]) * (limit + 1)
    sieve[0:2] = b"\x00\x00"
    for p in range(2, isqrt(limit) + 1):
        if sieve[p]:
            sieve[p * p :: p] = b"\x00" * ((limit - p * p) // p + 1)  # 从 p² 起标掉倍数
    return [p for p in range(2, limit + 1) if sieve[p]]


PRIMES = primes_upto(SIEVE_LIMIT)  # 1e4 内共 1229 个素数


@cache
def is_prime(m: int) -> bool:
    """试除判素：m ≤ 10^8 必有素因子 ≤ 10^4，故素数表已覆盖全部候选。"""
    if m < 2:
        return False
    return all(m % p for p in PRIMES if p * p <= m)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, k = next(data), next(data)
    xs = [next(data) for _ in range(n)]

    # 组合不关心顺序，itertools.combinations 恰好生成 C(n,k) 个下标递增的 k 元组，不重不漏；
    # @cache 让撞出相同和的组合（如全 1 数据）只判素一次。
    print(sum(is_prime(sum(chosen)) for chosen in combinations(xs, k)))


if __name__ == "__main__":
    solve()
