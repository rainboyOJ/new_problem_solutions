#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 02:08
# update_at: 2026-10-09 02:08

import sys

PI = 3.14159  # 题源约定（同题 1014 / 洛谷 B2014）；用 math.pi 会挂 7 个测试点


def solve() -> None:
    """读入半径 r，输出直径、周长、面积，数与数之间一个空格，各保留 4 位小数。"""
    data = iter(map(float, sys.stdin.buffer.read().split()))
    r = next(data, None)  # 单组输入：一行一个实数半径；空输入直接结束
    if r is None:
        return

    diameter = 2.0 * r             # 直径 d = 2r
    circumference = 2.0 * PI * r   # 周长 c = 2πr
    area = PI * r * r              # 面积 s = πr²

    print(f"{diameter:.4f} {circumference:.4f} {area:.4f}")


if __name__ == "__main__":
    solve()
