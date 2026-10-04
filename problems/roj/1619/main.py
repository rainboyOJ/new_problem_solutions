#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 22:41
# update_at: 2026-09-30 22:41

import sys

LIMIT = 46341          # floor(sqrt(2**31 - 1))，筛出这段小数就能覆盖 [L,R] 的全部合数
CLOSEST = "are closest, "
DISTANT = "are most distant."
NONE = "There are no adjacent primes."


def small_primes(n: int) -> list[int]:
    """返回 [2, n] 内的所有质数，作为区间筛的“试探除数”集合。"""
    sieve = bytearray([1]) * (n + 1)      # 1 表示暂时认为它是质数
    sieve[0:2] = b"\x00\x00"
    for i in range(2, int(n ** 0.5) + 1):
        if sieve[i]:
            sieve[i * i :: i] = bytearray(len(sieve[i * i :: i]))  # 质数 i 的倍数全是合数
    return [i for i in range(2, n + 1) if sieve[i]]


def segment_primes(L: int, R: int, base: list[int]) -> list[int]:
    """返回闭区间 [L, R] 内的所有质数，按升序排列。

    下标 i 对应数字 L+i，只筛这一段，内存取决于区间长度而不是 R 的大小。
    """
    width = R - L + 1
    is_prime = bytearray([1]) * width       # 先全部假定为质数，再被小质数划掉
    for p in base:
        if p * p > R:
            break
        # 从 >= L 的第一个 p 的倍数开始划；L 较小时下界不能低于 p 本身
        start = max(p * p, (L + p - 1) // p * p)
        is_prime[start - L :: p] = bytearray(len(range(start, R + 1, p)))
    if L == 1:                              # 1 既不是质数也不是合数，单独处理
        is_prime[0] = 0
    return [L + i for i in range(width) if is_prime[i]]


def best_pair(primes: list[int], want_max: bool) -> tuple[int, int]:
    """取相邻质数差最大（want_max=True）或最小的那一对，并列时取更靠前的。

    max/min 返回第一个达到极值的元素，正好满足“输出靠前的素数对”。
    """
    choose = max if want_max else min
    return choose(zip(primes, primes[1:]), key=lambda pair: pair[1] - pair[0])


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    base = small_primes(LIMIT)

    out: list[str] = []
    for i in range(0, len(data), 2):
        L, R = data[i], data[i + 1]
        primes = segment_primes(L, R, base)
        if len(primes) < 2:                 # 少于两个质数就没有“相邻质数对”
            out.append(NONE)
            continue
        lo_a, lo_b = best_pair(primes, want_max=False)
        hi_a, hi_b = best_pair(primes, want_max=True)
        out.append(f"{lo_a},{lo_b} {CLOSEST}{hi_a},{hi_b} {DISTANT}")

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
