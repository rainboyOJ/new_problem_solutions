#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 21:26
# update_at: 2026-09-29 21:30

import sys
from functools import cache


@cache
def fib_pair(n: int) -> tuple[int, int]:
    """返回 (F(n), F(n+1))，其中 F(0)=0、F(1)=1。

    倍增恒等式：F(2m)=F(m)·(2F(m+1)−F(m))，F(2m+1)=F(m)²+F(m+1)²。
    把下标折半就能一次拿到相邻两项 F(2m)、F(2m+1)，递归深度只有 O(log n)。
    """
    if n < 2:                     # 边界：(F(0),F(1))=(0,1)，(F(1),F(2))=(1,1)——第二项恒为 1
        return n, 1
    lo, hi = fib_pair(n >> 1)     # 下标折半，m = ⌊n/2⌋
    even = lo * (2 * hi - lo)     # F(2m)
    odd = lo * lo + hi * hi       # F(2m+1)
    return (odd, even + odd) if n & 1 else (even, odd)  # 奇数时再向前迈一步


def solve() -> None:
    n = int(sys.stdin.buffer.read())
    # 题面数列 0,1,1,2,3,5,... 是零起编号的斐波那契：第 n 项就是 F(n-1)
    print(fib_pair(n - 1)[0])


if __name__ == "__main__":
    solve()
