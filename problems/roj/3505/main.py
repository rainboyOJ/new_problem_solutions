#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 04:16
# update_at: 2026-10-02 04:16

import sys


def distinct_primes(k: int) -> int:
    """k 的不同质因数个数 ω(k)：试除到 √k，除尽的因子只计一次。"""
    count = 0
    d = 2
    while d * d <= k:
        if k % d == 0:
            count += 1
            while k % d == 0:  # 把 d 的整段幂次除尽，剩下的部分不再含 d
                k //= d
        d += 1
    return count + (k > 1)  # 剩余的 k 是一个大质数


def solve() -> None:
    x0, y0 = map(int, sys.stdin.buffer.read().split())

    # gcd(P,Q)=x0 且 lcm(P,Q)=y0 有解 ⇔ x0 | y0（gcd 必整除 lcm），否则答案为 0。
    if y0 % x0 != 0:
        print(0)
        return

    # 令 P=x0*a, Q=x0*b：gcd(a,b)=1 且 a*b=k（k=y0/x0）。
    # 互质要求把 k 的每个质因子整段幂次 p^e 全给 a 或全给 b，共 2^ω(k) 个有序对。
    k = y0 // x0
    print(1 << distinct_primes(k))


if __name__ == "__main__":
    solve()
