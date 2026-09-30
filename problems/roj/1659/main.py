#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 00:33
# update_at: 2026-10-01 00:33

import sys


def fact_pfree(n: int, p: int, pk: int) -> int:
    """n! 抽掉所有 p 因子后模 pk 的值。

    按 pk 分块：一个完整块 [1..pk] 内与 p 互素的数乘积是常数 block，
    完整块贡献 block^(n//pk)；零头块 [1..n%pk] 单独乘；
    再递归处理 n! 中每隔 p 个数的那一层（其乘积是 (n//p)!）。
    """
    if n == 0:
        return 1
    res = 1
    block = 1
    for i in range(1, pk + 1):
        if i % p:
            block = block * i % pk
    res = pow(block, n // pk, pk)
    for i in range(1, n % pk + 1):
        if i % p:
            res = res * i % pk
    return res * fact_pfree(n // p, p, pk) % pk


def small_comb(n: int, m: int, p: int, pk: int) -> int:
    """C(n, m) 模 pk（pk = p^k）：先算 p 的指数 e，再合成 p^e * 三个 p-free 阶乘。"""
    if m < 0 or m > n:
        return 0
    e = 0  # C(n, m) 里 p 的总指数：(n! 的) - (m! 的) - ((n-m)! 的)
    x = n
    while x:
        x //= p
        e += x
    x = m
    while x:
        x //= p
        e -= x
    x = n - m
    while x:
        x //= p
        e -= x

    if pk // (p ** e) == 0:  # p^e 已是 pk 的倍数，整个 C(n,m) ≡ 0 (mod pk)
        return 0

    unit = (
        fact_pfree(n, p, pk)
        * pow(fact_pfree(m, p, pk), -1, pk)
        % pk
        * pow(fact_pfree(n - m, p, pk), -1, pk)
        % pk
    )
    return pow(p, e, pk) * unit % pk


def crt(rests: list[int], mods: list[int]) -> int:
    """中国剩余定理：模数两两互素，逐个合并余数方程，返回模 ∏mods 下的解。"""
    M, res = 1, 0
    for a, q in zip(rests, mods):
        res += (a - res) * pow(M, -1, q) % q * M  # 把模 M 的解抬到模 M*q 且对 q 也对上 a
        M *= q
    return res % M


def factorize(x: int) -> list[tuple[int, int]]:
    """分解质因数，返回 [(质数 p, p 的幂 pk)]；P ≤ 1e9，试除到 √x 即可。"""
    res: list[tuple[int, int]] = []
    d = 2
    while d * d <= x:
        if x % d == 0:
            pk = 1
            while x % d == 0:
                x //= d
                pk *= d
            res.append((d, pk))
        d += 1
    return res + [(x, x)] if x > 1 else res


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    P, n, m = next(data), next(data), next(data)
    weights = [next(data) for _ in range(m)]

    if sum(weights) > n:  # 礼物要发完，总数超出 n 就没有可行方案
        print('Impossible')
        return

    # P = ∏ p_i^{c_i}：在每条 C(剩余人数, w_i) 上分别取模，再用 CRT 拼回模 P。
    factors = factorize(P)
    primes, powers = [p for p, _ in factors], [pk for _, pk in factors]
    rests = [1] * len(factors)
    for w in weights:
        rests = [r * small_comb(n, w, p, pk) % pk for r, p, pk in zip(rests, primes, powers)]
        n -= w  # 第 i 个人挑完后，剩余礼物数交给下一个人继续挑
    print(crt(rests, powers))


if __name__ == "__main__":
    solve()
