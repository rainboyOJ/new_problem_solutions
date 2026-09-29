#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 22:04
# update_at: 2026-09-29 22:13

import sys
from itertools import accumulate
from operator import mul


def solve() -> None:
    """读入 n，输出 S = 1! + 2! + ... + n! 的精确值。"""
    (n,) = map(int, sys.stdin.buffer.read().split())
    # accumulate(..., mul) 正是 C++ 里的那一步高精乘 a *= i：它依次产出 1!, 2!, ..., n!。
    # Python 的 int 是任意精度、乘法自带进位，所以不必再手写 mul/add 的进位循环。
    print(sum(accumulate(range(1, n + 1), mul)))


if __name__ == "__main__":
    solve()
