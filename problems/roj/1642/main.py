#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 23:43
# update_at: 2026-09-30 23:43

import sys

BASE = ((1, 1), (1, 0))  # 递推矩阵：F(n+1) = F(n) + F(n-1)


def mat_mul(a: tuple, b: tuple, mod: int) -> tuple:
    """2x2 矩阵乘法后取模：结果的第 i 行是 a 的第 i 行分别点乘 b 的两列。"""
    (a00, a01), (a10, a11) = a
    (b00, b01), (b10, b11) = b
    row0 = (a00 * b00 + a01 * b10) % mod, (a00 * b01 + a01 * b11) % mod
    row1 = (a10 * b00 + a11 * b10) % mod, (a10 * b01 + a11 * b11) % mod
    return row0, row1


def power(base: tuple, exp: int, mod: int) -> tuple:
    """矩阵快速幂：base 的 exp 次方，每步取模 m。"""
    result = ((1, 0), (0, 1))  # 单位矩阵，相当于乘法的 1
    while exp:
        if exp & 1:
            result = mat_mul(result, base, mod)
        base = mat_mul(base, base, mod)
        exp >>= 1
    return result


def solve() -> None:
    n, m = map(int, sys.stdin.buffer.read().split())
    # 由 [F(n+1), F(n); F(n), F(n-1)] = BASE^n 得 F(n) 是 BASE^(n-1) 的左上角；
    # n = 1 时幂为 0，单位矩阵的左上角正是 F(1) = 1。
    print(power(BASE, n - 1, m)[0][0] % m)


if __name__ == "__main__":
    solve()
