#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 23:37
# update_at: 2026-09-29 23:37

import sys


def factorize(n: int) -> list[tuple[int, int]]:
    """试除法分解 n：返回 (素因子, 指数) 列表，因子天然从小到大。"""
    factors: list[tuple[int, int]] = []
    d = 2
    while d * d <= n:  # 剩余的 n 若 >1，必然是一个素因子
        e = 0
        while n % d == 0:
            n //= d
            e += 1
        if e:
            factors.append((d, e))
        d += 1 if d == 2 else 2  # 2 之后只试奇数
    if n > 1:
        factors.append((n, 1))
    return factors


def solve() -> None:
    n = int(sys.stdin.readline())
    factors = factorize(n)
    # 输出表达式：指数为 1 时只写因子，否则写 a^b，用 * 连接
    print('*'.join(f'{p}^{e}' if e > 1 else str(p) for p, e in factors))


if __name__ == "__main__":
    solve()
