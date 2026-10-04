#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 15:04
# update_at: 2026-09-29 15:04

import math
import sys


def solve() -> None:
    """读入两端点坐标，按勾股定理求线段长度并保留 3 位小数。"""
    xa, ya, xb, yb = map(float, sys.stdin.buffer.read().split())  # 行结构不影响 token 顺序
    print(f"{math.hypot(xa - xb, ya - yb):.3f}")  # hypot = 内部带缩放的 sqrt(dx^2+dy^2)


if __name__ == "__main__":
    solve()
