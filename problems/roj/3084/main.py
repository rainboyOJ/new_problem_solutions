#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 15:52
# update_at: 2026-10-01 16:05

import sys
from itertools import count
from math import gcd


def can_finish(
    x: int, y: int, used: int, limit: int, p: int, widest: dict[tuple[int, int], int]
) -> bool:
    """在 limit-used 步的预算内，能否让某个工作变量恰好变成 P 次幂。

    x >= y >= 0 是两个工作变量此刻的指数；widest 记录「搜索到该状态时还剩多少步」的最大值。
    """
    if x == p or y == p:
        return True
    rest = limit - used
    if rest == 0:
        return False
    if x << rest < p:  # 一步至多让较大的指数翻倍，再走 rest 步也追不上 p
        return False
    if p % gcd(x, y):  # 两个变量永远是 gcd(x, y) 的倍数，p 也必须能被它整除
        return False
    if widest.get((x, y), -1) >= rest:  # 曾经用更宽的预算搜过同一个状态
        return False
    widest[(x, y)] = rest

    nxt = used + 1
    # 一步操作 = 从 {x+y, x-y, x+x, y+y} 取一个值写进某个工作变量，写回后按指数大小归一化
    for value in (x + y, x - y, x + x, y + y):
        for a, b in ((value, y), (x, value)):
            hi, lo = (a, b) if a >= b else (b, a)
            if can_finish(hi, lo, nxt, limit, p, widest):
                return True
    return False


def min_ops(p: int) -> int:
    """迭代加深：limit 从小到大，第一次搜到 P 次幂的层数就是最少操作数。"""
    for limit in count():
        if can_finish(1, 0, 0, limit, p, {}):
            return limit


def solve() -> None:
    p = next(iter(map(int, sys.stdin.buffer.read().split())))
    print(min_ops(p))


if __name__ == "__main__":
    solve()
