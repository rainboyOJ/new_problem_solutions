#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 09:06
# update_at: 2026-09-30 09:06

import sys
from math import isqrt


def is_prime(x: int) -> bool:
    """试除法判素数：只要 2 ~ √x 里没有因子就是素数。"""
    return x >= 2 and all(x % d for d in range(2, isqrt(x) + 1))


def is_palindrome(x: int) -> bool:
    """回文判断：十进制表示正读反读一致。"""
    s = str(x)
    return s == s[::-1]


def solve() -> None:
    n = int(sys.stdin.read().split()[0])
    # 11 到 n 逐个检查：先滤回文（便宜），幸存者再滤素数（试除），
    # 两个条件都满足才计数；两位回文数都是 11 的倍数，幸存者极少
    print(sum(1 for i in range(11, n + 1) if is_palindrome(i) and is_prime(i)))


if __name__ == "__main__":
    solve()
