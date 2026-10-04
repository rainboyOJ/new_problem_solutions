#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 09:57
# update_at: 2026-10-01 09:57

import sys
from collections.abc import Iterator

MOD = 9901  # 题面要求的取模常量


def factors(n: int) -> Iterator[tuple[int, int]]:
    """分解 n = ∏ p^e，依次产出 (p, e)。"""
    small = [p for p in (2, 3, 5) if n % p == 0]  # 先摘掉小质因子，省去开头的试探
    for p in small:
        e = 0
        while n % p == 0:
            n //= p
            e += 1
        yield p, e
    d = 7  # 已排除 2、3、5，剩下的质因子都落在 6k±1 上
    while d * d <= n:
        for p in (d, d + 4):  # 6k+1 与 6k+5 构成一对候选
            if n % p == 0:
                e = 0
                while n % p == 0:
                    n //= p
                    e += 1
                yield p, e
        d += 6
    if n > 1:  # 除完小因子后剩下的必然是质数
        yield n, 1


def divsum(p: int, terms: int) -> int:
    """等比数列 1+p+…+p^(terms-1) 对 9901 取模：按 terms 的二进制从高位往低位折半。"""
    f, g = 0, 1  # f = 1+p+…+p^(k-1)，g = p^k；k 是已经确定的项数
    for bit in bin(terms)[2:]:
        f, g = f * (g + 1) % MOD, g * g % MOD  # 项数翻倍：两段长度 k 的等比串首尾相接
        if bit == "1":  # 二进制这一位是 1：末尾再补一项 p^(2k)
            f, g = (f + g) % MOD, g * p % MOD
    return f


def sum_of_divisors(a: int, b: int) -> int:
    """求 A^B 的所有约数之和 mod 9901。"""
    if a == 0:  # 0 被所有正整数整除，约数和不是有限值；本题数据约定答案为 0
        return 0
    ans = 1
    for p, e in factors(a):  # A^B = ∏ p^(e·b)，各质因子的等比和彼此独立
        ans = ans * divsum(p % MOD, e * b + 1) % MOD  # 等比和共有 e·b+1 项
    return ans


def solve() -> None:
    a, b = map(int, sys.stdin.buffer.read().split())
    print(sum_of_divisors(a, b))


if __name__ == "__main__":
    solve()
