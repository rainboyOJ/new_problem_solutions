#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 23:43
# update_at: 2026-09-30 23:43

import sys

MOD = 9901  # 模数，且是素数；但 p≡1 (mod 9901) 时 p-1 不可逆，故不能用除法公式求等比和


def geometric(p: int, n: int) -> int:
    """求 1+p+...+p^n (mod MOD)，倍增法：只用乘加，不碰逆元。"""
    if n == 0:
        return 1 % MOD
    m = n >> 1
    if n & 1:  # n = 2m+1：S(n) = S(m) * (1 + p^(m+1))
        return geometric(p, m) * (1 + pow(p, m + 1, MOD)) % MOD
    # n = 2m：S(n) = S(m-1) * (1 + p^m) + p^(2m)
    return (geometric(p, m - 1) * (1 + pow(p, m, MOD)) + pow(p, 2 * m, MOD)) % MOD


def factorize(a: int) -> dict[int, int]:
    """试除分解 a，返回 {质因子: 指数}。"""
    factors: dict[int, int] = {}
    d = 2
    while d * d <= a:
        while a % d == 0:
            factors[d] = factors.get(d, 0) + 1
            a //= d
        d += 1
    if a > 1:  # 残留的是大于 sqrt(原 a) 的素因子，指数必为 1
        factors[a] = factors.get(a, 0) + 1
    return factors


def solve() -> None:
    A, B = map(int, sys.stdin.buffer.read().split())

    if B == 0 or A == 1:  # A^B = 1，唯一的约数是 1
        print(1)
        return
    if A == 0:  # 0 的正整数次幂是 0
        print(0)
        return

    ans = 1
    for p, e in factorize(A).items():
        ans = ans * geometric(p, e * B) % MOD
    print(ans)


if __name__ == "__main__":
    solve()
