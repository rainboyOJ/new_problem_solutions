#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 06:07
# update_at: 2026-10-01 06:07

import sys
from math import gcd


def interior_points(n: int, m: int, p: int) -> int:
    """返回三角形 (0,0),(n,m),(p,0) 内部（不含边界）的整点数。

    Pick 定理 I = S - B/2 + 1；这里改用两倍量避免小数：
    I = (2S - B + 2) / 2，其中 2S = p*m，B 是三条边上的整点数之和。
    """
    area2 = p * m                                          # 鞋带公式的两倍面积
    boundary = gcd(n, m) + gcd(abs(p - n), m) + p           # 三条边的 gcd 之和
    return (area2 - boundary + 2) // 2


def solve() -> None:
    n, m, p = map(int, sys.stdin.buffer.read().split())
    print(interior_points(n, m, p))


if __name__ == "__main__":
    solve()
