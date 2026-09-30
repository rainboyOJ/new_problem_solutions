#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 22:43
# update_at: 2026-09-30 22:43

from math import prod
from sys import stdin

MOD = 10**9 + 7


def solve() -> None:
    n = int(stdin.buffer.read())

    # 线性筛：只记录每个合数的最小质因子，其余因数分解全靠它跳转。
    min_prime = [0] * (n + 1)
    primes: list[int] = []
    for v in range(2, n + 1):
        if min_prime[v] == 0:              # v 没有更小的质因子 → v 是质数
            min_prime[v] = v
            primes.append(v)
        for p in primes:
            if p > min_prime[v] or p * v > n:
                break
            min_prime[p * v] = p

    # 先把 2..n 每个数的质因子指数累加起来，得到 n! 的标准分解。
    exp = [0] * (n + 1)
    for v in range(2, n + 1):
        while v > 1:
            p = min_prime[v]
            while v % p == 0:              # 除尽同一个质因子
                v //= p
                exp[p] += 1

    # ans = d((n!)^2)：n! 里指数为 E 的质因子，平方后指数 2E，贡献 2E+1。
    print(prod(2 * e + 1 for e in exp) % MOD)


if __name__ == "__main__":
    solve()
