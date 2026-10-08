#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 22:08
# update_at: 2026-10-08 22:08

import sys


def gcd_euclid(a: int, b: int) -> int:
    """辗转相除法（欧几里得算法）求 gcd(a, b)，迭代版，不依赖 sys.setrecursionlimit。

    依据 gcd(a, b) = gcd(b, a % b)：每步新除数严格小于旧除数，序列单调下降，
    必在有限步后余数为 0；此时 a 整除原两个数，且任何公约数都整除它，故 a 即 gcd。
    """
    while b:
        a, b = b, a % b
    return a


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    m, n = next(data), next(data)
    print(gcd_euclid(m, n))


if __name__ == "__main__":
    solve()
