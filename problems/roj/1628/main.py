#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys
import math
from functools import reduce
from operator import mul

# 预处理素数表（由于 x <= 2^20 ≈ 1048576，质因子分解只需要试除到 sqrt(x) <= 1024）
MAX_P = 1024
IS_PRIME = [True] * (MAX_P + 1)
IS_PRIME[0] = IS_PRIME[1] = False
for i in range(2, int(MAX_P**0.5) + 1):
    if IS_PRIME[i]:
        IS_PRIME[i * i : MAX_P + 1 : i] = [False] * len(range(i * i, MAX_P + 1, i))
PRIMES = [i for i, p in enumerate(IS_PRIME) if p]


def factorize(x: int) -> list[int]:
    """分解正整数 x 的质因数，返回各质因子的出现次数列表。"""
    counts = []
    for p in PRIMES:
        if p * p > x:
            break
        if x % p == 0:
            cnt = 0
            while x % p == 0:
                cnt += 1
                x //= p
            counts.append(cnt)
    if x > 1:
        counts.append(1)
    return counts


def solve() -> None:
    lines = sys.stdin.read().split()
    if not lines:
        return
    for line in lines:
        x = int(line)
        counts = factorize(x)
        max_len = sum(counts)
        # 多重集的排列数：(sum(counts))! / (count_1! * count_2! * ... * count_k!)
        ans = math.factorial(max_len) // reduce(mul, (math.factorial(c) for c in counts), 1)
        print(f"{max_len} {ans}")


if __name__ == "__main__":
    solve()
