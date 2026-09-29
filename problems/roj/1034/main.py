#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 15:04
# update_at: 2026-09-29 15:04

import sys


def triangle_area(x1: float, y1: float, x2: float, y2: float, x3: float, y3: float) -> float:
    """以 (x1, y1) 为公共起点的两条边向量做叉积，绝对值的一半即三角形面积。"""
    return abs((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1)) / 2


def solve() -> None:
    x1, y1, x2, y2, x3, y3 = map(float, sys.stdin.read().split())
    area = triangle_area(x1, y1, x2, y2, x3, y3)
    print(f"{area:.2f}")  # 固定保留两位小数，四舍五入


if __name__ == "__main__":
    solve()
