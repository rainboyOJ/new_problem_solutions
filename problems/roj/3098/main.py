#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 17:00
# update_at: 2026-10-01 17:00

import sys
from collections.abc import Iterator


def prime_powers(n: int) -> Iterator[tuple[int, int]]:
    """把 n 分解质因数，依次产出 (质因子 p, 指数 a)，即 n = ∏ p^a。"""
    p = 2
    while p * p <= n:
        if n % p == 0:
            a = 0
            while n % p == 0:
                n //= p
                a += 1
            yield p, a
        p += 1
    if n > 1:  # 除完所有 ≤ √n 的因子后还剩的大于 1 的部分必然是质数
        yield n, 1


def answer(n: int) -> int:
    """求 ∑_{1 ≤ i ≤ n} gcd(i, n)：答案关于 n 是积性的，在每个质因子幂上乘一个局部因子。"""
    total = 1
    for p, a in prime_powers(n):
        total *= p ** (a - 1) * (p + a * (p - 1))
    return total


def solve() -> None:
    n = int(sys.stdin.buffer.read())  # 输入只有一个整数 N
    print(answer(n))


if __name__ == "__main__":
    solve()
