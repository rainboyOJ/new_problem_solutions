#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 08:25
# update_at: 2026-10-02 08:25

from itertools import count
from math import gcd, isqrt


def divisors_of(b1: int) -> list[int]:
    """返回 b1 的全部约数：试除出 <=sqrt(b1) 的 d，再配对 b1//d。

    b1 ≤ 2×10⁹，√b1 ≈ 44722，逐个试除即可；同一 d 与 b1//d 去重靠 i*i <= b1
    时只取一个。
    """
    divs = [d for d in range(1, isqrt(b1) + 1) if b1 % d == 0]
    divs += [b1 // d for d in reversed(divs) if b1 // d != d]
    return divs


def count_x(a0: int, a1: int, b0: int, b1: int) -> int:
    """统计满足 gcd(x,a0)=a1 且 lcm(x,b0)=b1 的正整数 x 的个数。"""
    total = sum(
        1
        for d in divisors_of(b1)
        if d % a1 == 0                                  # gcd(x,a0) 必是 x 的约数
        and gcd(d, a0) == a1
        and d * b0 == b1 * gcd(d, b0)                   # lcm(x,b0)·gcd(x,b0)=x·b0
    )
    return total


def solve() -> None:
    data = iter(map(int, open(0).read().split()))
    n = next(data)
    for _ in range(n):
        a0, a1, b0, b1 = (next(data) for _ in range(4))
        print(count_x(a0, a1, b0, b1))


if __name__ == "__main__":
    solve()
