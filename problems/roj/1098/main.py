#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 18:39
# update_at: 2026-09-29 18:39

import sys


def solve() -> None:
    n = int(sys.stdin.readline())

    # 两个不同质数相乘，较小的那个必定 ≤ sqrt(n)，
    # 从小到大试除，找到的第一个因子就是较小质数。
    p = next(d for d in range(2, int(n**0.5) + 1) if n % d == 0)

    print(n // p)  # 较大质数 = n / 较小质数


if __name__ == "__main__":
    solve()
