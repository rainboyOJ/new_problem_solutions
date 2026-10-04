#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 01:10
# update_at: 2026-10-01 01:10

import sys
from math import comb


def solve() -> None:
    n = next(iter(map(int, sys.stdin.buffer.read().split())))

    # 方案数就是第 n 个卡特兰数 C(2n,n)/(n+1)；math.comb 是精确大整数运算，
    # 先整除再输出，n <= 500 时结果有 297 位也不会溢出。
    print(comb(2 * n, n) // (n + 1))


if __name__ == "__main__":
    solve()
