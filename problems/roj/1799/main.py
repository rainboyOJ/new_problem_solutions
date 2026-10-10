#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 03:52
# update_at: 2026-10-08 03:52

import sys

MOD = 10 ** 9 + 7  # 取模质数 p；指数降幂用它的周期 p-1
PERIOD = MOD - 1


def reduce_mod(digits: str, m: int) -> int:
    """把十进制数字串按 Horner 法逐位取模，避开 int() 的 4300 位字符串上限。"""
    r = 0
    for ch in digits:
        r = (r * 10 + (ord(ch) - 48)) % m
    return r


def solve() -> None:
    # 输入只有一行一个大整数：取出该 token，去掉前导零（题面保证 n >= 3）。
    token = next(iter(sys.stdin.buffer.read().split()))
    n_digits = token.decode().lstrip('0') or '0'

    n_mod_p = reduce_mod(n_digits, MOD)        # n mod p，用于 n^2 + n + 2
    n_mod_pm1 = reduce_mod(n_digits, PERIOD)   # n mod (p-1)，费马小定理降幂用
    exponent = (n_mod_pm1 + 1) % PERIOD        # (n+1) mod (p-1)

    ans = (pow(2, exponent, MOD) - n_mod_p * n_mod_p - n_mod_p - 2) % MOD
    print(ans)


if __name__ == "__main__":
    solve()
