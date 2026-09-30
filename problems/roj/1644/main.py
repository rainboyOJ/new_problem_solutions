#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 23:43
# update_at: 2026-09-30 23:43

import sys


def fib_pair(n: int, mod: int) -> tuple[int, int]:
    """返回 (F(n) mod m, F(n+1) mod m)：快速倍增，由 F(k),F(k+1) 一步翻倍到 F(2k),F(2k+1)。"""
    if n == 0:
        return (0, 1 % mod)              # m = 1 时所有 Fibonacci 值都应输出 0
    a, b = fib_pair(n >> 1, mod)         # a = F(k), b = F(k+1)，k = ⌊n/2⌋
    c = a * (2 * b - a) % mod            # F(2k)   = F(k) · (2F(k+1) - F(k))
    d = (a * a + b * b) % mod            # F(2k+1) = F(k)² + F(k+1)²
    if n & 1:                            # n 是奇数：再从 F(2k), F(2k+1) 走一步
        return (d, (c + d) % mod)
    return (c, d)


def solve() -> None:
    n, m = map(int, sys.stdin.buffer.read().split())

    fn, fn1 = fib_pair(n, m)
    fn2 = (fn + fn1) % m                 # F(n+2)
    fn3 = (fn1 + fn2) % m                # F(n+3)
    # 恒等式 T(n) = Σ i·F(i) = n·F(n+2) - F(n+3) + 2 (mod m)，推导见题解
    print((n * fn2 - fn3 + 2) % m)


if __name__ == "__main__":
    solve()
