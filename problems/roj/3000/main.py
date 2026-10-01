#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 09:05
# update_at: 2026-10-01 09:05

import sys


def mod_pow(base: int, exponent: int, mod: int) -> int:
    """快速幂：把指数拆成二进制位，逐位平方底数，只把为 1 的那些位乘进结果。"""
    result = 1 % mod  # p = 1 时任何数取模都是 0，这一行顺手处理掉该边界
    base %= mod       # a 可能大于 p，先取模能让后续乘法保持在小整数范围内
    while exponent:
        if exponent & 1:  # 最低位为 1：这一份 base^(2^k) 要乘进答案
            result = result * base % mod
        base = base * base % mod  # base^(2^k) -> base^(2^(k+1))
        exponent >>= 1            # 换到下一位
    return result


def solve() -> None:
    a, b, p = map(int, sys.stdin.buffer.read().split())
    print(mod_pow(a, b, p))


if __name__ == "__main__":
    solve()
