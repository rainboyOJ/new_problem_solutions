#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 05:05
# update_at: 2026-10-02 05:05

import sys


def catalan(n: int) -> int:
    """第 n 个卡特兰数：C_k = C_{k-1} * 2(2k-1) / (k+1)，整除在乘法之后做。"""
    count = 1  # C_0 = 1：空序列只有一种"什么都不做"的方案
    for k in range(2, n + 1):
        count = count * 2 * (2 * k - 1) // (k + 1)
    return count


def solve() -> None:
    n = int(sys.stdin.readline())
    print(catalan(n))


if __name__ == "__main__":
    solve()
