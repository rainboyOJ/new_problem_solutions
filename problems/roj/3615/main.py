#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 10:43
# update_at: 2026-10-02 10:43

import sys
from fractions import Fraction
from math import gcd


def best_ratio(a: int, b: int, limit: int) -> tuple[int, int]:
    """在分子、分母都不超过 limit 的既约分数里，找不小于 a/b 且与 a/b 差最小的那个。

    两个候选分数的差只取决于 x、y，用 Fraction 精确比较大小避免浮点误差；
    差相同时按 (x, y) 升序取最先枚举到的。
    """
    candidates = (
        (x, y)                                        # 合法候选：互质且 x/y >= a/b
        for x in range(1, limit + 1)
        for y in range(1, limit + 1)
        if gcd(x, y) == 1 and x * b >= a * y
    )
    return min(candidates, key=lambda p: (Fraction(p[0] * b - a * p[1], p[1] * b), p))


def solve() -> None:
    a, b, limit = map(int, sys.stdin.buffer.read().split())  # 题面的 A、B、L
    print(*best_ratio(a, b, limit))


if __name__ == "__main__":
    solve()
