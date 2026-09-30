#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 12:00
# update_at: 2026-09-30 12:00

import sys

BASE = 131
MOD = 1_000_000_007


def build_sieve(n: int) -> list[int]:
    """线性筛预处理每个数的最小质因数。"""
    min_p = list(range(n + 1))
    primes: list[int] = []
    for i in range(2, n + 1):
        if min_p[i] == i:
            primes.append(i)
        for p in primes:
            if p * i > n:
                break
            min_p[p * i] = p
            if i % p == 0:
                break
    return min_p


def get_prime_factors(x: int, min_p: list[int]) -> list[int]:
    """质因数分解，返回 x 的所有质因数列表（含重数）。"""
    factors: list[int] = []
    while x > 1:
        p = min_p[x]
        factors.append(p)
        x //= p
    return factors


def is_period(a: int, b: int, k: int, h: list[int], power: list[int]) -> bool:
    """检验长度为 k 的前缀是否为 S[a..b] 的循环节。

    S[a..b] 长度为 L = b - a + 1。
    若 k 为周期，则 S[a .. b - k] 与 S[a + k .. b] 相同。
    """
    # 子串 S[a..b-k] 的哈希值 vs 子串 S[a+k..b] 的哈希值
    h1 = (h[b - k] - h[a - 1] * power[b - k - a + 1]) % MOD
    h2 = (h[b] - h[a + k - 1] * power[b - a - k + 1]) % MOD
    return h1 == h2


def solve() -> None:
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    it = iter(input_data)
    n = int(next(it))
    s = next(it)
    q = int(next(it))

    # 预处理字符串哈希与幂次
    h = [0] * (n + 1)
    power = [1] * (n + 1)
    for i, ch in enumerate(s, 1):
        power[i] = (power[i - 1] * BASE) % MOD
        h[i] = (h[i - 1] * BASE + ord(ch)) % MOD

    min_p = build_sieve(n)

    out: list[str] = []
    for _ in range(q):
        a = int(next(it))
        b = int(next(it))
        length = b - a + 1

        factors = get_prime_factors(length, min_p)
        ans = length
        for p in factors:
            cand = ans // p
            if is_period(a, b, cand, h, power):
                ans = cand

        out.append(str(ans))

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
