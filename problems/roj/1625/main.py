#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 22:45
# update_at: 2026-09-30 22:45

import sys

# 前 10 个质数连乘已经超过 2*10^9 (2*3*5*...*29 = 6469693230 > 2*10^9)
PRIMES = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29]


def search(p_idx: int, max_exp: int, num: int, divs: int, bound: int, best: list[int]) -> None:
    """递归搜索质因子指数不增的候选数，维护约数最多且数值最小的解。

    best 结构：[best_num, max_divs]
    """
    better_divs = divs > best[1]
    same_divs_smaller = divs == best[1] and num < best[0]
    if better_divs or same_divs_smaller:
        best[0], best[1] = num, divs

    if p_idx == len(PRIMES):
        return

    p = PRIMES[p_idx]
    cur = num
    for exp in range(1, max_exp + 1):
        cur *= p
        if cur > bound:
            break
        search(p_idx + 1, exp, cur, divs * (exp + 1), bound, best)


def max_antiprime(n: int) -> int:
    """计算不大于 n 的最大反素数。"""
    best = [1, 1]  # [best_number, max_divisors]
    search(0, 31, 1, 1, n, best)
    return best[0]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    print(max_antiprime(n))


if __name__ == "__main__":
    solve()
