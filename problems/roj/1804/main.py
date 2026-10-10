#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 04:13
# update_at: 2026-10-08 04:13

import sys
from itertools import accumulate
from math import isqrt

type Primes = list[int]     # 不超过 sqrt(N) 的质数，升序
type Prefix = list[int]     # sp[j] = 前 j 个质数之和


def build_primes(limit: int) -> tuple[Primes, Prefix]:
    """线性筛出 [2, limit] 的质数，并给出质数前缀和。"""
    comp = bytearray(limit + 1)
    primes: Primes = []
    for i in range(2, limit + 1):
        if not comp[i]:
            primes.append(i)
        for p in primes:                        # 线性筛：每个合数只被最小质因子划去
            if i * p > limit:
                break
            comp[i * p] = 1
            if i % p == 0:
                break
    return primes, [0, *accumulate(primes)]


def comp_sum(n: int) -> int:
    """返回 [1, n] 内所有合数的最大真因数之和。

    合数 c 的最大真因数 = c / spf(c)（spf 为最小质因子）。按 spf=p 把合数分组后，
    第 p 组的贡献 Σm 恰好是 min_25 筛里被 p 划去的那些数之和再除以 p，
    所以只需要滚动维护 g[w] = 「质数或最小质因子 > 已筛质数」的 2..w 数值和。
    """
    if n < 4:
        return 0                                # 1、2、3 都不是合数
    S = isqrt(n)
    primes, sp = build_primes(S)
    # 状态值 val = floor(n/i) 只会取 2*sqrt(n) 个值：val > S 的按 i 存进 g1，
    # val <= S 的直接拿 val 当下标存进 g2；i = 1..n//(S+1) 恰好覆盖所有 val > S。
    L = n // (S + 1)
    g1 = [0, *[(n // i) * (n // i + 1) // 2 - 1 for i in range(1, L + 1)]]
    g2 = [x * (x + 1) // 2 - 1 for x in range(S + 1)]

    ans = 0
    for j, p in enumerate(primes, 1):
        pre = sp[j - 1]                         # 小于 p 的质数之和，即 g 里要留下的质数部分
        p2 = p * p
        for i in range(1, min(L, n // p2) + 1):  # 只有 val >= p^2 的状态才含 p 的倍数
            k = i * p                           # 状态 n//i 除以 p 之后对应 floor(n/k)
            cur = g1[k] if k <= L else g2[n // k]
            d = cur - pre
            if i == 1:
                ans += d                        # 状态 n：最小质因子恰为 p 的合数贡献 Σm
            g1[i] -= d * p
        for x in range(S, p2 - 1, -1):          # 倒序保证读到的是上一阶段的 g2[x//p]
            g2[x] -= (g2[x // p] - pre) * p
    return ans


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    l, r = next(data), next(data)
    print(comp_sum(r) - comp_sum(l - 1))        # 前缀和作差，区间内每个合数贡献不变


if __name__ == "__main__":
    solve()
