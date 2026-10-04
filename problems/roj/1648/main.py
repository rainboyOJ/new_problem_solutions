#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 23:55
# update_at: 2026-09-30 23:55

import sys
from math import comb

MOD = 10007  # 题面指定的模数（是质数，但 k <= 1000 时直接算精确组合数再取模即可）


def coefficient(a: int, b: int, k: int, n: int, m: int) -> int:
    """二项式定理：(ax+by)^k 展开后 x^n y^m 的系数 = C(k,n) * a^n * b^m。"""
    return comb(k, n) * pow(a, n, MOD) % MOD * pow(b, m, MOD) % MOD


def solve() -> None:
    a, b, k, n, m = map(int, sys.stdin.buffer.read().split())
    print(coefficient(a, b, k, n, m))


if __name__ == "__main__":
    solve()
