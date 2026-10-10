#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 02:20
# update_at: 2026-10-09 07:37

import sys
from math import sqrt


def solve() -> None:
    """读入三边长，海伦公式求面积，保留 3 位小数。"""
    data = iter(map(float, sys.stdin.buffer.read().split()))
    a = next(data, None)
    b = next(data, None)
    c = next(data, None)
    if a is None or b is None or c is None:   # 缺输入保护
        return

    p = (a + b + c) / 2.0                      # 半周长
    s2 = p * (p - a) * (p - b) * (p - c)       # 海伦公式的被开方项
    if not (s2 > 0.0):                         # -0.0 / 极小负数 / NaN 归零，防 sqrt 返回 nan
        s2 = 0.0

    print(f"{sqrt(s2):.3f}")


if __name__ == "__main__":
    solve()
