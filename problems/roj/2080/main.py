#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 07:21
# update_at: 2026-10-01 07:33

import sys
import math
from collections.abc import Callable

BOUND = 100.0  # 题给坐标范围：最优点必落在 [0, 100]^2 内（沿轴投影不会让任何距离变大）
TERNS = 60     # 三分轮数：区间每轮缩到 2/3，(2/3)^60 ≈ 2.7e-9，远小于输出的 0.1 精度


def seg_dist(px: float, py: float, x1: float, y1: float, x2: float, y2: float) -> float:
    """点到线段的距离：把点投影到线段所在直线，参数 t 夹到 [0, 1] 即得最近点。"""
    dx = x2 - x1
    dy = y2 - y1
    length2 = dx * dx + dy * dy
    if length2 == 0:  # 退化成点：垂足公式会除零，直接算点距
        return math.hypot(px - x1, py - y1)
    t = ((px - x1) * dx + (py - y1) * dy) / length2
    t = 0.0 if t < 0 else 1.0 if t > 1 else t  # 夹紧到线段内部，是"点-线段"而非"点-直线"的距离
    return math.hypot(px - (x1 + t * dx), py - (y1 + t * dy))


def total_length(segs: list[tuple[int, int, int, int]], px: float, py: float) -> float:
    """g(x, y)：电源放在 (px, py) 时，连到每段电网所需的电线总长。"""
    return sum(seg_dist(px, py, *s) for s in segs)


def minimize_1d(f: Callable[[float], float]) -> float:
    """一维凸函数 f 在 [0, BOUND] 上的最小值点：三分每轮把区间缩到 2/3。

    凸性保证"较小的那个内点外侧"一定不含最小值点，所以每轮丢掉的那一段可以放心舍弃。
    """
    lo, hi = 0.0, BOUND
    for _ in range(TERNS):
        m1 = lo + (hi - lo) / 3
        m2 = hi - (hi - lo) / 3
        if f(m1) < f(m2):
            hi = m2
        else:
            lo = m1
    return (lo + hi) / 2


def best_on_line(segs: list[tuple[int, int, int, int]], px: float) -> float:
    """固定 x = px，求 g 关于 y 的最小值位置：内层三分。"""
    return minimize_1d(lambda py: total_length(segs, px, py))


def on_line_min(segs: list[tuple[int, int, int, int]], px: float) -> float:
    """h(x)：固定 x = px 的整条竖线上，电线总长能达到的最小值。"""
    return total_length(segs, px, best_on_line(segs, px))


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    f = next(data)  # 题面的 F
    segs = [(next(data), next(data), next(data), next(data)) for _ in range(f)]

    # h 是凸函数（凸函数的边缘最小化仍凸），所以外层还能再套一层三分：
    # 外层比较的是"整条竖线上的最小值"，而不是某两个点上的值。
    x = minimize_1d(lambda px: on_line_min(segs, px))
    y = best_on_line(segs, x)
    print(f"{x:.1f} {y:.1f} {total_length(segs, x, y):.1f}")


if __name__ == "__main__":
    solve()
