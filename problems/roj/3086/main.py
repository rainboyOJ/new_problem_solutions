#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 16:13
# update_at: 2026-10-01 16:19

import sys
from math import isqrt


def sieve(n: int) -> bytearray:
    """埃氏筛：返回长度 n+1 的表，is_prime[i] 非 0 表示 i 是质数。"""
    is_prime = bytearray([1]) * (n + 1)          # 先全部当质数，再划掉合数
    is_prime[:2] = bytes(min(2, n + 1))          # 0 和 1 不是质数
    for i in range(2, isqrt(n) + 1):
        if is_prime[i]:
            # 从 i*i 起把 i 的倍数清成 0：切片赋值一次清空整段，长度用 range 数出来
            is_prime[i * i :: i] = bytes(len(range(i * i, n + 1, i)))
    return is_prime


def legendre(p: int, n: int) -> int:
    """勒让德公式：n! 中质数 p 的指数 = n//p + n//p^2 + n//p^3 + ..."""
    power, count = n, 0
    while power:
        power //= p
        count += power
    return count


def solve() -> None:
    it = iter(sys.stdin.buffer.read().split())
    n = int(next(it, 0))

    # n! 的质因数只可能是 <= n 的质数，筛出它们再逐个套勒让德公式
    is_prime = sieve(n)
    out = [f"{p} {legendre(p, n)}" for p in range(2, n + 1) if is_prime[p]]
    # 每个质数至少贡献一个因子，必有 c >= 1，所以非空时直接 join 就是题面要求的分行输出
    sys.stdout.write("\n".join(out) + "\n" if out else "")


if __name__ == "__main__":
    solve()
