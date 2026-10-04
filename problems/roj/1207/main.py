#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 23:37
# update_at: 2026-09-29 23:41

import sys


def gcd(a: int, b: int) -> int:
    """返回 a 与 b 的最大公约数：反复把 (a, b) 换成 (b, a % b)，b 归零时 a 就是答案。"""
    while b:
        a, b = b, a % b  # 余数严格变小，所以循环次数是 O(log min(a, b))
    return a


def solve() -> None:
    """读入一行里的两个正整数，输出它们的最大公约数。"""
    a, b = map(int, sys.stdin.buffer.read().split())
    print(gcd(a, b))


if __name__ == "__main__":
    solve()
