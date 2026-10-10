#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 02:12
# update_at: 2026-10-08 02:12

import sys

MOD = 999983  # 题目要求的取模值
SLOT = 8      # 每个系数占的字节数：系数 < 2^20，卷积和 < 2^53，槽之间不会进位串扰

# 把多项式打包成一个大整数：第 s 个槽（SLOT 字节，即第 s·SLOT·8 位）存 x^s 的系数。
# 于是「两个多项式相乘」等价于「两个大整数相乘」，整条卷积由 CPython 的大整数乘法一次算完。
type Poly = tuple[int, int]  # (打包后的大整数, 次数上界)


def mul(a: Poly, b: Poly) -> Poly:
    """多项式乘法：大整数相乘得到全部卷积和，再逐槽取模压回。"""
    packed, deg = a[0] * b[0], a[1] + b[1]
    body = packed.to_bytes((deg + 1) * SLOT, "little")
    slots = (int.from_bytes(body[i:i + SLOT], "little") % MOD for i in range(0, len(body), SLOT))
    return int.from_bytes(b"".join(s.to_bytes(SLOT, "little") for s in slots), "little"), deg


def power(base: Poly, e: int) -> Poly:
    """快速幂：返回 base 的 e 次幂多项式。"""
    result: Poly = (1, 0)  # 常数多项式 1，即「0 位、数位和为 0 的方案数为 1」
    squares = base
    while e:
        if e & 1:
            result = mul(result, squares)
        e >>= 1
        if e:
            squares = mul(squares, squares)
    return result


def same_sum_pairs(poly: Poly) -> int:
    """Σ_s c_s² mod MOD：两段 k 位序列「数位和相等」的配对方案数。

    系数 c_s 表示「用 S 中数字构成 k 位、数位和为 s」的方案数；两段各自独立取数，
    只需数位和相同，故配对方案数恰为系数平方和。
    """
    packed, deg = poly
    body = packed.to_bytes((deg + 1) * SLOT, "little")
    return sum(int.from_bytes(body[i:i + SLOT], "little") ** 2
               for i in range(0, len(body), SLOT)) % MOD


def count_good(base: Poly, n: int) -> int:
    """按容斥公式计数：2·S(P^n) − S(P^⌈n/2⌉)·S(P^⌊n/2⌋)，其中 P = Σ_{d∈S} x^d，S 即 same_sum_pairs。"""
    half = power(base, n // 2)                # P^⌊n/2⌋
    odd = mul(half, base) if n % 2 else half  # P^⌈n/2⌉
    whole = mul(half, odd)                    # P^n = P^⌊n/2⌋ · P^⌈n/2⌉
    # 前 n 位之和 = 后 n 位之和、奇数位之和 = 偶数位之和 两个事件的方案数相同（均为 S(P^n)）；
    # 交集由「s1 = s4 且 s2 = s3」解耦，等于两个独立配对的乘积。
    return (2 * same_sum_pairs(whole) - same_sum_pairs(odd) * same_sum_pairs(half)) % MOD


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n = int(next(data))
    given = next(data)                          # 题面给的长度不超过 10 的字符串
    digits = sorted({ch - 48 for ch in given})  # 去重：题面说的是「数字集合」
    base: Poly = (sum(1 << (d * SLOT * 8) for d in digits), max(digits))  # Σ_{d∈S} x^d
    print(count_good(base, n))


if __name__ == "__main__":
    solve()
