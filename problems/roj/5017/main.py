#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 19:48
# update_at: 2026-10-08 19:57

import sys
from collections import Counter

MOD = 10**9 + 7  # 方案数的模，和题目给的质数 p 是两回事


def half_products(values: list[int], p: int) -> list[int]:
    """折半枚举：返回这一半所有子集（含空集）乘积 mod p 的列表。"""
    prods = [1]
    for v in values:
        prods += [x * v % p for x in prods]  # 每个已有子集再决定选不选 v
    return prods


def count_schemes(a: list[int], p: int, c: int) -> int:
    """折半搜索：左半积 x 需要右半积 y 满足 x*y ≡ c (mod p)，即 y ≡ c * x^{-1}。

    0 没有模逆元，先把它们剔出来：设 z = 0 的个数、m = 剩余非零元素个数，
    含至少一个 0 的非空子集共 (2^z - 1) * 2^m 个，它们的积恒为 0，故只在 c == 0 时全部合法。
    """
    if c >= p:  # 余数一定小于 p，不可能命中
        return 0

    zeros = a.count(0)
    nz = [x for x in a if x != 0]  # 非零元素才能进折半配对
    half = len(nz) // 2

    need = Counter(c * pow(x, p - 2, p) % p for x in half_products(nz[:half], p))
    total = sum(need[y] for y in half_products(nz[half:], p))  # Counter 缺键默认 0
    if c == 1:
        total -= 1  # 减掉左右都取空集这一种（要求至少取一个数）

    # c == 0 时含 0 的子集全部命中；c != 0 时它们全部落空，无需计入
    zero_part = (pow(2, zeros, MOD) - 1) * pow(2, len(nz), MOD) % MOD if c == 0 else 0
    return (total + zero_part) % MOD


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, p, c = next(data), next(data), next(data)
    a = [next(data) for _ in range(n)]
    print(count_schemes(a, p, c) % MOD)


if __name__ == "__main__":
    solve()
