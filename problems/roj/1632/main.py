#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 23:08
# update_at: 2026-09-30 23:08

import sys


def exgcd(a: int, b: int) -> tuple[int, int, int]:
    """扩展欧几里得算法：返回 (g, x, y) 使得 a*x + b*y = g = gcd(a, b)。"""
    if b == 0:
        return a, 1, 0
    g, x1, y1 = exgcd(b, a % b)
    return g, y1, x1 - (a // b) * y1


def solve() -> None:
    data = sys.stdin.read().split()
    if not data:
        return
    a, b = map(int, data)
    _, x, _ = exgcd(a, b)
    # 调整为最小正整数解
    ans = (x % b + b) % b
    print(ans if ans != 0 else b)


if __name__ == "__main__":
    solve()
