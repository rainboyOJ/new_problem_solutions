#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-06 10:30
# update_at: 2026-07-06 10:30

import sys

LIMIT = 10**5  # 题面保证 X, Y <= 10^5


def sieve_primes(limit: int) -> list[bool]:
    """埃氏筛：is_prime[n] 表示 n 是否为素数。"""
    is_prime = [True] * (limit + 1)
    is_prime[:2] = [False, False]                     # 0 和 1 不是素数
    for n in range(2, int(limit**0.5) + 1):
        if is_prime[n]:
            is_prime[n * n :: n] = [False] * len(is_prime[n * n :: n])
    return is_prime


def solve() -> None:
    x, y = map(int, sys.stdin.buffer.read().split())  # 两数无大小顺序，统一成闭区间 [lo, hi]
    lo, hi = min(x, y), max(x, y)

    is_prime = sieve_primes(LIMIT)
    print(sum(is_prime[lo : hi + 1]))                 # 前缀和相减也可以，这里直接区间求和


if __name__ == "__main__":
    solve()
