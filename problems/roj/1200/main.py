#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 23:20
# update_at: 2026-09-29 23:20

import sys
from functools import cache
from math import isqrt

MIN_FACTOR = 2  # 题面要求每个因子 a_i 都大于 1；它同时是"选取下一个因子的下界"初值


@cache
def count(n: int, lo: int) -> int:
    """把 n 拆成若干个 >= lo 的因子之积（无序、因子可重复）的方案数。

    `lo` 是当前这一位因子的下界：上一轮选了 d，剩下 n/d 的下界就是 d，
    保证因子序列非降序，从而每个无序分解只被数一次。
    结果含"单因子 n 本身"这一种分解，所以初值取 1。
    """
    # 只枚举不超过 sqrt(n) 的首因子：再大的首因子会强迫第二位小于自己，违反非降序
    return 1 + sum(count(n // d, d) for d in range(lo, isqrt(n) + 1) if n % d == 0)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    T = next(data)

    # 递归只在 n % d == 0 且 d <= isqrt(n) 时发生，于是 n//d >= d，调用点恒有 n >= lo；
    # 题面又保证 a > 1，所以永远不会走到 n < lo 这种会多算 1 的边界。
    out = [count(next(data), MIN_FACTOR) for _ in range(T)]
    print('\n'.join(map(str, out)))


if __name__ == "__main__":
    solve()
