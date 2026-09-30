#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 00:46
# update_at: 2026-10-01 00:46

import sys
from functools import reduce
from operator import xor


def solve() -> None:
    """Nim 博弈：先手必胜当且仅当各堆石子数的异或和不为 0。"""
    data = iter(sys.stdin.buffer.read().split())
    n = int(next(data))
    piles = [int(next(data)) for _ in range(n)]
    nim_sum = reduce(xor, piles)  # Nim 和：把每堆数量按位异或起来
    print("win" if nim_sum else "lose")


if __name__ == "__main__":
    solve()
