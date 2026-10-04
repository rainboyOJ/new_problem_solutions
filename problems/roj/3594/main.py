#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 09:40
# update_at: 2026-10-02 09:40

import sys


def smallest_factor(n: int) -> int:
    """试除找 n 的最小质因数：n 最多两个不同质因子，试到 √n 必然命中一个。"""
    d = 2
    while d * d <= n:
        if n % d == 0:
            return d
        d += 1 if d == 2 else 2  # 除 2 之后只需试奇数
    return n  # 兜底：n 本身是质数（题目保证不会走到这里）


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    p = smallest_factor(n)  # 最小的那个质因数
    print(n // p)           # 另一个必然更大


if __name__ == "__main__":
    solve()
