#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 09:16
# update_at: 2026-09-30 09:16

import sys
from math import isqrt

LIMIT = 100000  # N 的上界：任意 x ≤ LIMIT 的反序数也 ≤ LIMIT，一张筛表覆盖全部判素需求


def reversed_number(n: int) -> int:
    """反序数：把 n 的十进制数字倒过来组成的数，前导 0 自动消失（100000 → 1）。"""
    return int(str(n)[::-1])


# 埃氏筛：IS_PRIME[i] = 1 当且仅当 i 是素数，覆盖 [0, LIMIT]
IS_PRIME = bytearray([1]) * (LIMIT + 1)
IS_PRIME[0] = IS_PRIME[1] = 0
for i in range(2, isqrt(LIMIT) + 1):
    if IS_PRIME[i]:
        IS_PRIME[i * i :: i] = bytearray(len(range(i * i, LIMIT + 1, i)))  # 从 i² 起、步长 i 的位置全是合数


def truth_primes_in(m: int, n: int) -> list[str]:
    """[m, n] 内的真素数：自身与反序数都在筛表中；反序数可能落在区间外，查的是同一张全局筛表。"""
    return [str(i) for i in range(m, n + 1) if IS_PRIME[i] and IS_PRIME[reversed_number(i)]]


def solve() -> None:
    m, n = map(int, sys.stdin.buffer.read().split())
    ans = truth_primes_in(m, n)
    print(','.join(ans) if ans else 'No')


if __name__ == "__main__":
    solve()
