#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 04:55
# update_at: 2026-10-08 04:55

import sys

MOD = 10000     # 题面要求对 10000 取余
MAX_DIGIT = 10  # n <= 10^9，位数不超过 10 位


def power_mod(base: int, exp: int, mod: int) -> int:
    """快速幂：返回 base 的 exp 次方对 mod 取余。"""
    result = 1
    base %= mod
    while exp:
        if exp & 1:
            result = result * base % mod
        base = base * base % mod
        exp >>= 1
    return result


def digit_length_sum(n: int) -> int:
    """返回 D mod 10000，其中 D 是 1..n 每个数的十进制位数之和。

    按位数分段：len 位数的区间是 [10^(len-1), 10^len - 1]，与 1..n 求交后整段累加。
    """
    total = 0
    for length in range(1, MAX_DIGIT + 1):
        low = 10 ** (length - 1)          # 本段的起点
        if low > n:
            break                         # 后面更长的位数段一定也为空
        high = min(n, low * 10 - 1)       # 本段落在 1..n 内的终点
        total = (total + (high - low + 1) * length) % MOD
    return total


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    # 展开式总长 t(n) = 2^(n-1)(n + D) + 2^n + 3n + D - 4
    digit_sum = digit_length_sum(n)
    answer = (
        power_mod(2, n - 1, MOD) * (n + digit_sum)                  # 2^(n-1) * (n + D)
        + power_mod(2, n, MOD)                                      # 2^n
        + 3 * n + digit_sum - 4                                     # 3n + D - 4
    ) % MOD
    print(answer)


if __name__ == "__main__":
    solve()
