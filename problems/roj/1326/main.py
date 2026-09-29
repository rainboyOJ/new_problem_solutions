#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 05:19
# update_at: 2026-09-30 05:19

import sys


def power_mod(b: int, p: int, k: int) -> int:
    """快速幂：求 b^p mod k。

    p 的每一个二进制位从低位到高位依次考察：基数平方升级、位为 1 就乘进答案。
    每一步都取模，保证中间值不超过 k^2，不会溢出（Python 大整数下只是让数字保持小、
    乘法变快）。
    """
    ans = 1
    b %= k                                    # 先把底数降到 [0, k) 再平方，防 k=1 之外还白乘大数
    while p:
        if p & 1:                             # 当前二进制位是 1：这一份底数要乘进答案
            ans = ans * b % k
        b = b * b % k                         # 底数平方升级：b^1 -> b^2 -> b^4 -> ...
        p >>= 1                               # 去掉已经考察过的最低位
    return ans


def solve() -> None:
    b, p, k = map(int, sys.stdin.buffer.read().split())
    print(f"{b}^{p} mod {k}={power_mod(b, p, k)}")


if __name__ == "__main__":
    solve()
