#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 23:39
# update_at: 2026-09-29 23:39

import sys
from math import gcd
from functools import reduce


def add(acc: tuple[int, int], s: str) -> tuple[int, int]:
    """把当前累加和 acc=a/b 与分数 s=p/q 相加，返回最简形式。"""
    a, b = acc
    p, q = map(int, s.split('/'))
    x, y = a * q + b * p, b * q
    g = gcd(x, y)
    return x // g, y // g


def solve() -> None:
    data = sys.stdin.buffer.read().decode().split()
    n = int(data[0])
    a, b = reduce(add, data[1:], (0, 1))
    print(a if b == 1 else f"{a}/{b}")


if __name__ == "__main__":
    solve()
