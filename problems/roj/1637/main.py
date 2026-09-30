#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-04-18 10:00
# update_at: 2026-04-18 10:00

import sys
from itertools import combinations
from math import gcd

NO_COLLISION = True
COLLIDED = False


def extgcd(a: int, b: int) -> tuple[int, int, int]:
    """扩展欧几里得算法：返回 (g, x, y) 使得 a*x + b*y = g = gcd(a, b)。"""
    if b == 0:
        return a, 1, 0
    g, x1, y1 = extgcd(b, a % b)
    return g, y1, x1 - (a // b) * y1


def can_meet(
    c1: int, p1: int, l1: int, c2: int, p2: int, l2: int, m: int
) -> bool:
    """判断两个野人在给定山洞数 m 下，是否会在共同有生之年相遇。"""
    # 方程为：(p1 - p2) * x ≡ c2 - c1 (mod m)
    a = p1 - p2
    b = c2 - c1
    g, x, _ = extgcd(a, m)

    if b % g != 0:
        return False

    step = abs(m // g)
    x = (x * (b // g)) % step
    if x < 0:
        x += step

    limit = min(l1, l2)
    return x <= limit


def is_valid_m(
    savages: list[tuple[int, int, int]], m: int
) -> bool:
    """验证山洞总数为 m 时，所有野人之间是否均无冲突。"""
    for (c1, p1, l1), (c2, p2, l2) in combinations(savages, 2):
        if can_meet(c1, p1, l1, c2, p2, l2, m):
            return COLLIDED
    return NO_COLLISION


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data, None)
    if n is None:
        return

    savages = [(next(data), next(data), next(data)) for _ in range(n)]
    m = max(c for c, _, _ in savages)

    while True:
        if is_valid_m(savages, m):
            print(m)
            return
        m += 1


if __name__ == "__main__":
    solve()
