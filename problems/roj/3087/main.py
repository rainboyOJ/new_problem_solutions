#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 16:14
# update_at: 2026-10-01 16:14

import sys
from math import isqrt

VALUE_LIMIT = 2 * 10**9  # 题面给出的取值上界：a0、a1、b0、b1 都不超过 2·10^9
UNBOUNDED = 10**9       # 指数只被单侧限制时的上界哨兵（任何指数都远小于它）


def primes_upto(limit: int) -> tuple[int, ...]:
    """筛出不超过 limit 的质数：分解 a0 与 b1 时，试除只需用到 √(2·10^9) 以内的质数。"""
    sieve = bytearray([1]) * (limit + 1)
    sieve[0:2] = bytes(2)  # 0 和 1 不是质数
    for p in range(2, isqrt(limit) + 1):
        if sieve[p]:
            sieve[p * p :: p] = bytes(len(range(p * p, limit + 1, p)))  # 从 p² 起划掉 p 的倍数
    return tuple(i for i, ok in enumerate(sieve) if ok)


PRIMES = primes_upto(isqrt(VALUE_LIMIT))  # 4648 个质数


def exponent_count(a: int, a1: int, b0: int, b1: int) -> int:
    """固定质数 p 后，合法指数 e = v_p(x) 的取值个数；四个参数是 a0、a1、b0、b1 的 v_p。

    两个条件各自把 e 限制成「一个定值」或「一段区间」：
    1. min(e, a) = a1：若 a1 < a 则 e 只能是 a1，否则 e ⩾ a1；
    2. max(e, b0) = b1：若 b0 < b1 则 e 只能是 b1，否则 e ⩽ b1。
    两者的交集长度就是这一位上 e 的方案数，交集为空返回 0（整题答案随之变成 0）。
    """
    lo1, hi1 = (a1, a1) if a1 < a else (a1, UNBOUNDED)   # 条件 1 对 e 的限制
    lo2, hi2 = (b1, b1) if b0 < b1 else (0, b1)          # 条件 2 对 e 的限制
    low, high = max(lo1, lo2), min(hi1, hi2)
    return max(0, high - low + 1)


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    out: list[str] = []
    n = int(next(data))

    for _ in range(n):
        a0, a1, b0, b1 = int(next(data)), int(next(data)), int(next(data)), int(next(data))
        total = 1

        # 逐质数处理：p 不同时整除 a0 与 b1 时四个指数全是 0，这一位的方案数固定为 1。
        # 两数边除边缩小，p² 一旦超过剩下的最大者，剩下的部分就必定是 1 或一个质数。
        for p in PRIMES:
            if p * p > max(a0, b1):
                break
            if a0 % p and b1 % p:
                continue

            count_a = count_a1 = count_b0 = count_b1 = 0
            while a0 % p == 0:
                a0, count_a = a0 // p, count_a + 1
            while a1 % p == 0:  # a1 | a0，指数一定不超过上面那个
                a1, count_a1 = a1 // p, count_a1 + 1
            while b0 % p == 0:  # b0 | b1，同理
                b0, count_b0 = b0 // p, count_b0 + 1
            while b1 % p == 0:
                b1, count_b1 = b1 // p, count_b1 + 1
            total *= exponent_count(count_a, count_a1, count_b0, count_b1)

        # 剩下的四段都是 1 或某个大质数（指数只能取 0/1），且互不相同，逐个收尾。
        # q > √(2·10^9) 保证 q² 超出值域，所以 v 被 q 整除就等价于 v == q。
        for q in {a0, a1, b0, b1} - {1}:
            exponents = [int(v % q == 0) for v in (a0, a1, b0, b1)]
            total *= exponent_count(*exponents)

        out.append(str(total))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
