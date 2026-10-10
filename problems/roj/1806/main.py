#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-02-14 09:30
# update_at: 2026-02-14 09:30

import sys
from functools import cache
from math import gcd, isqrt

NO_SOLUTION = "Math Error"  # 类型 2 无解时的输出（题目要求的固定字符串）

type BabySteps = dict[int, int]  # 值 -> 该值下最大的小步指数 j
type FactorPowers = list[tuple[int, int]]  # [(p, p^a), ...]：不同质因子各自聚成一项


def exgcd(a: int, b: int) -> tuple[int, int, int]:
    """返回 (g, x, y) 使得 a*x + b*y = g = gcd(a, b)。"""
    if b == 0:
        return a, 1, 0
    g, x, y = exgcd(b, a % b)
    return g, y, x - a // b * y


def inv_mod(a: int, m: int) -> int:
    """求 a 在模 m 下的逆元，要求 gcd(a, m) = 1。"""
    return exgcd(a % m, m)[1] % m


def pow_mod(a: int, b: int, m: int) -> int:
    """快速幂：a^b mod m（Python 内置 pow 已同阶，这里直接透传以对齐 C++）。"""
    return pow(a, b, m)


def log_discrete(a: int, b: int, p: int) -> int:
    """扩展 BSGS：求 a^x ≡ b (mod p) 的最小非负整数 x，无解返回 -1。"""
    a %= p
    b %= p
    if p == 1:
        return 0  # 模 1 下一切同余成立，最小 x = 0
    if b == 1:
        return 0  # a^0 = 1
    # 消去 gcd(a, p)：d = gcd(a,p) 必须整除 b，否则无解；之后 p ← p/d, b ← b/d
    cnt, k = 0, 1
    d = gcd(a, p)
    while d != 1:
        if b % d:
            return -1
        b //= d
        p //= d
        k = k * (a // d) % p
        cnt += 1
        if b == k:
            return cnt  # x = cnt 已成立，且它是最小的
        d = gcd(a, p)
    if p == 1:
        return cnt
    # 标准 BSGS：令 x - cnt = i*m - j，则 k*(a^m)^i ≡ b*a^j (mod p)
    m = isqrt(p) + 1
    baby: BabySteps = {}
    cur = b
    for j in range(m + 1):
        baby[cur] = j  # 同值覆盖成更大的 j，保证 i*m - j 最小
        cur = cur * a % p
    base = pow_mod(a, m, p)
    cur = k
    for i in range(1, m + 1):
        cur = cur * base % p
        if cur in baby:
            return i * m - baby[cur] + cnt
    return -1


def factor_prime_powers(n: int) -> FactorPowers:
    """把 n 分解成 [(p, p^a), ...]，同一个质数的幂聚成一项。"""
    fac: FactorPowers = []
    d = 2
    while d * d <= n:
        if n % d == 0:
            pk = 1
            while n % d == 0:
                n //= d
                pk *= d
            fac.append((d, pk))
        d += 1
    if n > 1:
        fac.append((n, n))
    return fac


def count_p_in_fact(n: int, p: int) -> int:
    """n! 中质因子 p 的个数（Legendre 公式）。"""
    s = 0
    while n:
        n //= p
        s += n
    return s


@cache
def coprime_cycle(p: int, pk: int) -> int:
    """一个完整周期内所有与 p 互质之数的乘积 mod p^a，即 ∏_{1≤i≤p^a, p∤i} i。"""
    cycle = 1
    for i in range(1, pk + 1):
        if i % p:
            cycle = cycle * i % pk
    return cycle


def fac_without_p(n: int, p: int, pk: int) -> int:
    """n! 剔除全部质因子 p 后模 p^a 的值：整周期用幂、余项直接乘，再递归 ⌊n/p⌋!。"""
    res = 1
    while n:
        res = res * pow(coprime_cycle(p, pk), n // pk, pk) % pk
        partial = 1
        for i in range(1, n % pk + 1):
            if i % p:
                partial = partial * i % pk
        res = res * partial % pk
        n //= p
    return res


def comb_mod_prime_power(n: int, m: int, p: int, pk: int) -> int:
    """C(n, m) mod p^a（p 为质数）：提出全部 p 因子后，剩余部分与 p^a 互质可求逆元。"""
    if m < 0 or m > n:
        return 0
    e = count_p_in_fact(n, p) - count_p_in_fact(m, p) - count_p_in_fact(n - m, p)
    if e < 0 or pow(p, e, pk) == 0:
        return 0  # e ≥ a，组合数被 p^a 整除
    res = pow(p, e, pk) * fac_without_p(n, p, pk) % pk
    res = res * inv_mod(fac_without_p(m, p, pk), pk) % pk
    return res * inv_mod(fac_without_p(n - m, p, pk), pk) % pk


def fac_small(a: int, k: int, p: int) -> int:
    """C(a, k) mod p，其中 0 ≤ k ≤ a < p（此时 k! 与 p 互质，可以直接求逆元）。"""
    num = den = 1
    for j in range(1, k + 1):
        num = num * (a - k + j) % p
        den = den * j % p
    return num * pow(den, p - 2, p) % p


def lucas_prime(n: int, m: int, p: int) -> int:
    """C(n, m) mod p（p 为质数），Lucas 定理逐位算小组合数。"""
    if m < 0 or m > n:
        return 0
    res = 1
    while n or m:
        a, b = n % p, m % p
        if b > a:
            return 0  # 该位小组合数为 0
        res = res * fac_small(a, min(b, a - b), p) % p  # 用对称性少乘一半
        n //= p
        m //= p
    return res


def comb_mod(y: int, z: int, P: int) -> int:
    """C(z, y) mod P（P 可为合数）：逐质数幂算 + CRT 合并。"""
    n, m = z, y
    if P == 1:
        return 0
    if m < 0 or m > n:
        return 0
    if m == 0 or m == n:
        return 1 % P
    fac = factor_prime_powers(P)
    if len(fac) == 1 and fac[0][0] == P:
        return lucas_prime(n, m, P)  # P 本身是质数
    x, M = 0, 1
    for p, pk in fac:
        r = comb_mod_prime_power(n, m, p, pk)
        t = (r - x) % pk * inv_mod(M % pk, pk) % pk
        x = (x + M * t) % (M * pk)
        M *= pk
    return x


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    N = next(data)
    for _ in range(N):
        op, y, z, P = next(data), next(data), next(data), next(data)
        if op == 1:
            out.append(str(pow_mod(y, z, P)))
        elif op == 2:
            r = log_discrete(y, z, P)
            out.append(NO_SOLUTION if r < 0 else str(r))
        else:
            out.append(str(comb_mod(y, z, P)))
    print("\n".join(out))


if __name__ == "__main__":
    solve()
