#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 16:14
# update_at: 2026-10-01 16:20

from math import gcd
from sys import stdin


def factorize(n: int) -> list[tuple[int, int]]:
    """返回 n 的质因数分解 [(p, e), ...]：试除到 sqrt(n)，余数大于 1 时本身就是质因子。"""
    factors, p = [], 2
    while p * p <= n:
        if n % p == 0:
            e = 0
            while n % p == 0:
                n //= p
                e += 1
            factors.append((p, e))
        p += 1
    return factors + ([(n, 1)] if n > 1 else [])


def euler_phi(factors: list[tuple[int, int]]) -> int:
    """由质因数分解算 phi(n) = prod (p-1) * p^(e-1)。"""
    phi = 1
    for p, e in factors:
        phi *= (p - 1) * p ** (e - 1)
    return phi


def all_divisors(factors: list[tuple[int, int]]) -> list[int]:
    """由质因数分解升序生成全部正因数。"""
    divisors = [1]
    for p, e in factors:
        divisors = [d * p ** k for d in divisors for k in range(e + 1)]
    return sorted(divisors)


def multiplicative_order(a: int, mod: int) -> int:
    """返回 a 模 mod 的阶（最小的 n 使 a^n ≡ 1），调用前保证 gcd(a, mod) = 1。

    欧拉定理给出 a^phi ≡ 1，而 a^k ≡ 1 的解集是阶的倍数集，故阶必整除 phi；
    在 phi 的升序因数里取第一个可行者即为阶。
    """
    phi = euler_phi(factorize(mod))
    return next(d for d in all_divisors(factorize(phi)) if pow(a, d, mod) == 1)


def smallest_lucky_length(L: int) -> int:
    """L 的倍数中最小的全 8 数的位数；不存在这样的数时返回 0。"""
    # n 位全 8 数 = 8*(10^n - 1)/9，条件 L | 8*(10^n - 1)/9 等价于 9L/g | (10^n - 1)，
    # 其中 g = gcd(9L, 8) = gcd(L, 8)；于是问题变成 10^n ≡ 1 (mod 9L/g) 的最小 n。
    m = 9 * L // gcd(L, 8)
    return 0 if gcd(m, 10) != 1 else multiplicative_order(10, m)


def solve() -> None:
    out: list[str] = []
    case = 0
    for L in map(int, stdin.buffer.read().split()):
        if L == 0:  # 0 是输入终止标记，本身不处理
            break
        case += 1
        out.append(f"Case {case}: {smallest_lucky_length(L)}")
    print("\n".join(out))


if __name__ == "__main__":
    solve()
