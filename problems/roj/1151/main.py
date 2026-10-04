#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-07 10:00
# update_at: 2026-07-07 10:00

import sys


def sieve_count(n: int) -> int:
    """埃拉托斯特尼筛：返回 [2, n] 中素数个数。"""
    if n < 2:
        return 0
    is_prime = bytearray(b"\x01") * (n + 1)   # 1 表示待判定为素数
    is_prime[0:2] = b"\x00\x00"               # 0 和 1 不是素数
    for p in range(2, int(n ** 0.5) + 1):
        if is_prime[p]:
            step = p
            start = p * p
            is_prime[start:n + 1:step] = b"\x00" * ((n - start) // step + 1)
    return is_prime.count(1)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    print(sieve_count(n))


if __name__ == "__main__":
    solve()
