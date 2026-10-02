#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 19:18
# update_at: 2026-10-02 19:18

import math
import sys
from fractions import Fraction

FULL = Fraction(4096)  # 内存占满阈值：4GB = 4096MB


def solve() -> None:
    x_s, y_s = sys.stdin.read().split()
    xf, yf = float(x_s), float(y_s)

    # 浮点对数只做初始估计：求最小 m 使 x·y^m ≥ 4096（第 m+1 分钟占满）
    m = max(0, math.ceil(math.log(4096 / xf) / math.log(yf) - 1e-9))

    # 用精确有理数校验边界（等号成立的临界靠它判定），把估计值收敛到真正的最小 m
    x, y = Fraction(x_s), Fraction(y_s)
    while m > 0 and x * y ** (m - 1) >= FULL:
        m -= 1
    while x * y ** m < FULL:
        m += 1

    print(m + 1)  # 第 1 分钟占用 x，占满发生在第 m+1 分钟


if __name__ == "__main__":
    solve()
