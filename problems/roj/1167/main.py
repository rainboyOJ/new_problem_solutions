#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-01-18 09:00
# update_at: 2026-01-18 09:00

import sys
from functools import cache


@cache
def f(x: float, n: int) -> float:
    """递归计算连分式 f(x,n) = x / (n + f(x,n-1))，边界 f(x,1)=x/(1+x)。"""
    return x / (1 + x) if n == 1 else x / (n + f(x, n - 1))


def solve() -> None:
    data = iter(map(float, sys.stdin.buffer.read().split()))
    x = next(data)
    n = int(next(data))
    print(f"{f(x, n):.2f}")


if __name__ == "__main__":
    solve()
