#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-03-31 10:00
# update_at: 2026-03-31 10:00

import sys
from functools import reduce


def comb_small(n: int, m: int, p: int) -> int:
    """计算单步较小规模组合数 C(n, m) mod p，要求 n, m < p。"""
    if m < 0 or m > n:
        return 0
    m = min(m, n - m)
    # 分子 (n-m+1)*...*n，分母 1*...*m
    num = reduce(lambda a, b: a * b % p, range(n - m + 1, n + 1), 1)
    den = reduce(lambda a, b: a * b % p, range(1, m + 1), 1)
    return num * pow(den, p - 2, p) % p


def lucas(n: int, m: int, p: int) -> int:
    """根据 Lucas 定理计算 C(n, m) mod p，将 n, m 转为 p 进制逐位计算。"""
    ans = 1
    while n > 0 or m > 0:
        ans = ans * comb_small(n % p, m % p, p) % p
        n //= p
        m //= p
    return ans


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    T = next(data)
    out = [str(lucas(next(data), next(data), next(data))) for _ in range(T)]
    print("\n".join(out))


if __name__ == "__main__":
    solve()
