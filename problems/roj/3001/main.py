#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 09:43
# update_at: 2026-10-01 09:43

import sys


def mod_mul(a: int, b: int, mod: int) -> int:
    """龟速乘：把 b 按二进制拆成若干 2 的幂之和，用逐位翻倍的加法代替乘法。"""
    result = 0
    a %= mod            # a 可能不小于 p，先取模把加数压回 [0, p)，后续加法才不越界
    while b:
        if b & 1:                       # 最低位为 1：这一份 a*2^k 要加进答案
            result = (result + a) % mod
        a = (a + a) % mod               # a*2^k -> a*2^(k+1)，翻倍加法代替乘 2
        b >>= 1                         # 换到下一位
    return result


def solve() -> None:
    a, b, p = map(int, sys.stdin.buffer.read().split())
    print(mod_mul(a, b, p))


if __name__ == "__main__":
    solve()
