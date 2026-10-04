#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-11-18 20:00
# update_at: 2026-11-18 20:00

import sys

PI = 3.14159  # 题面规定的圆周率取值，不要用 math.pi


def solve() -> None:
    data = iter(map(float, sys.stdin.buffer.read().split()))
    r = next(data)  # 半径 0 < r <= 10000

    diameter = 2 * r               # 直径
    circumference = 2 * PI * r     # 周长 2πr
    area = PI * r * r              # 面积 πr²

    # 三个量各出现一次，逐个命名后交给 f-string 统一保留 4 位小数
    print(f"{diameter:.4f} {circumference:.4f} {area:.4f}")


if __name__ == "__main__":
    solve()
