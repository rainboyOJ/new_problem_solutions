#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 22:56
# update_at: 2026-10-08 22:56

import sys
from math import isqrt

MAXN = 1000000              # 数组余量（题面上限仅 1000，与 C++ 侧保持一致）


def sieve(n: int) -> list[int]:
    """筛法（埃拉托色尼筛）：返回 2..n 内的全部质数，由小到大。"""
    is_prime = [True] * (n + 1)
    is_prime[:2] = [False, False]                    # 0 和 1 不是质数
    # 外层只需枚举到 sqrt(n)：合数必有不超过 sqrt(n) 的质因数
    for p in range(2, isqrt(n) + 1):
        if not is_prime[p]:
            continue                                 # 已被更小的质数筛掉
        # 从 p*p 起标记：p 的较小倍数都含更小的质因数，早已被筛过
        for j in range(p * p, n + 1, p):
            is_prime[j] = False
    return [i for i in range(2, n + 1) if is_prime[i]]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data, 0)           # 无输入时取 0，直接走下面的保护分支
    if n < 2 or n > MAXN:
        return                  # 题面保证 2 <= n <= 1000，与 C++ 侧保持同一保护
    sys.stdout.write(''.join(f"{p}\n" for p in sieve(n)))


if __name__ == "__main__":
    solve()
