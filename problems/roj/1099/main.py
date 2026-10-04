#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-06 10:30
# update_at: 2026-07-06 10:30

import sys
import math


def nth_prime(n: int) -> int:
    """返回第 n 小的质数（n >= 1）。用埃氏筛预筛到足够范围。"""
    # 第 10000 个质数是 104729，筛到 105000 足够；为保险按 n*12 向上取整。
    limit = max(2, int(n * (math.log(n) + math.log(math.log(n))) + 12) if n >= 6 else 12)
    sieve = bytearray(b"\x01") * (limit + 1)
    sieve[0:2] = b"\x00\x00"
    for i in range(2, int(limit ** 0.5) + 1):
        if sieve[i]:
            sieve[i * i : limit + 1 : i] = b"\x00" * ((limit - i * i) // i + 1)
    # 枚举时直接计数，第 n 个质数即为答案。
    count = 0
    for i, is_p in enumerate(sieve):
        if is_p:
            count += 1
            if count == n:
                return i
    return -1  # 理论上不会到达


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    n = int(data[0])
    print(nth_prime(n))


if __name__ == "__main__":
    solve()
