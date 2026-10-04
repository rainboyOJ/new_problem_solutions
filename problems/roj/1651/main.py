#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 00:09
# update_at: 2026-10-01 00:22

import sys
from functools import cache
from math import isqrt

MOD = 999911659
# 指数 P 只需 mod (MOD-1)（费马小定理；G 不是 MOD 的倍数时成立）。
# MOD-1 = 999911658 = 2 × 3 × 4679 × 35617，四个两两互素的素因子，
# 所以每个素因子下用 Lucas 定理求 P，再用中国剩余定理合并回 mod (MOD-1)。
CRT_MODS = (2, 3, 4679, 35617)


def divisors(n: int) -> list[int]:
    """n 的全部正约数，按从小到大返回。"""
    low, high = [], []
    for d in range(1, isqrt(n) + 1):
        if n % d == 0:
            low.append(d)
            if d != n // d:  # 完全平方数时中间那个约数只算一次
                high.append(n // d)
    return low + high[::-1]


@cache
def pascal_row(p: int) -> tuple[tuple[int, ...], tuple[int, ...]]:
    """模 p 意义下的阶乘表与阶乘逆元表，用来 O(1) 查 C(a, b) mod p（a, b < p）。"""
    fact = [1] * p
    for i in range(1, p):
        fact[i] = fact[i - 1] * i % p
    inv = [1] * p
    inv[p - 1] = pow(fact[p - 1], -1, p)  # p 是质数且 p ∤ (p-1)!，末项可逆
    for i in range(p - 1, 0, -1):
        inv[i - 1] = inv[i] * i % p  # 由 1/i! 倒推出 1/(i-1)!
    return tuple(fact), tuple(inv)


def lucas(n: int, k: int, p: int) -> int:
    """C(n, k) mod p（p 为质数）。

    逐位拆开 n、k 的 p 进制表示：C(n, k) ≡ ∏ C(n_i, k_i) (mod p)。
    某一位上 k_i > n_i 时整个乘积为 0，这正是 p | C(n, k) 的情形，
    所以不需要像扩展 Lucas 那样单独处理 p 的幂次。
    """
    if k < 0 or k > n:
        return 0
    fact, inv = pascal_row(p)
    result = 1
    while n or k:
        ni, ki = n % p, k % p
        if ki > ni:
            return 0
        result = result * fact[ni] % p * inv[ki] % p * inv[ni - ki] % p
        n, k = n // p, k // p
    return result


def reduced_exponent(n: int) -> int:
    """P mod (MOD-1)，其中 P = Σ_{k | n} C(n, k)。"""
    ks = divisors(n)  # 四个模数共用同一份约数表，只需枚举一次
    r, M = 0, 1  # 已合并部分的余数与模数，M 始终与下一个素因子互素
    for p in CRT_MODS:
        residue = sum(lucas(n, k, p) for k in ks) % p
        t = (residue - r) * pow(M, -1, p) % p  # 令 r + t * M ≡ residue (mod p)
        r, M = r + t * M, M * p
    return r


def ancient_pig(n: int, g: int) -> int:
    """研究古代文字的代价 G^P mod 999911659，P 是对全部约数 k 的 C(n, n/k) 之和。"""
    if g % MOD == 0:
        return 0  # G 是模数的倍数，任何正次幂都是 0
    # n/k 也遍历全部约数，所以对 k 求和与对 n/k 求和是同一件事
    return pow(g, reduced_exponent(n), MOD)


def solve() -> None:
    n, g = map(int, sys.stdin.buffer.read().split())
    print(ancient_pig(n, g))


if __name__ == "__main__":
    solve()
