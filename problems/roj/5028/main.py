#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 22:19
# update_at: 2026-10-08 22:22

import sys


def solve() -> None:
    """读入 n，单层循环递推累加 1! + 2! + ... + n!；Python 整数无溢出问题。"""
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    fac = 1    # fac：当前项 i!（初始 1 表示 0!）
    total = 0  # total：1! + 2! + ... + i!
    for i in range(1, n + 1):
        fac *= i      # 利用 i! = (i-1)! * i，避免每次从头连乘
        total += fac

    print(total)


if __name__ == "__main__":
    solve()
