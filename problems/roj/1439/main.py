#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 10:23
# update_at: 2026-09-30 10:34

import sys
from collections.abc import Callable
from math import hypot

Point = tuple[float, float]

A: Point = (0.0, 0.0)  # 起点，也是 AB 的左端点
B: Point = (0.0, 0.0)  # AB 的右端点
C: Point = (0.0, 0.0)  # CD 的左端点
D: Point = (0.0, 0.0)  # 终点，也是 CD 的右端点
P = 1.0                # AB 上的移动速度
Q = 1.0                # CD 上的移动速度
R = 1.0                # 平面上（不踩传送带）的移动速度


def dist(u: Point, v: Point) -> float:
    """两点间的欧氏距离。"""
    return hypot(u[0] - v[0], u[1] - v[1])


def on_seg(seg: tuple[Point, Point], t: float) -> Point:
    """线段上参数为 t 的点：t=0 是起点，t=1 是终点。"""
    (x1, y1), (x2, y2) = seg
    return (x1 + t * (x2 - x1), y1 + t * (y2 - y1))


def belt_time(t: float, s: float) -> float:
    """走 A →X(t)→Y(s)→ D 的总时间：AB 段速度 P、中途飞行 R、CD 段速度 Q。"""
    x = on_seg((A, B), t)  # 在 AB 上的下车点
    y = on_seg((C, D), s)  # 在 CD 上的上车点
    return dist(A, x) / P + dist(x, y) / R + dist(y, D) / Q


def ternary_min(f: Callable[[float], float], lo: float, hi: float) -> float:
    """对 [lo, hi] 上的单峰（凸）函数 f 做实数三分，返回最小值。"""
    for _ in range(100):
        m1 = lo + (hi - lo) / 3
        m2 = hi - (hi - lo) / 3
        if f(m1) < f(m2):
            hi = m2
        else:
            lo = m1
    return f((lo + hi) / 2)


def entry_time(t: float) -> float:
    """固定 AB 上的下车点 X(t)，选好 CD 上的上车点后能达到的最短全程时间。"""
    return ternary_min(lambda s: belt_time(t, s), 0.0, 1.0)


def minimum_time() -> float:
    """全程最短时间：外层三分下车点，内层三分上车点。"""
    return ternary_min(entry_time, 0.0, 1.0)


def solve() -> None:
    """读入坐标与速度，输出 A 到 D 的最短时间，保留两位小数。"""
    global A, B, C, D, P, Q, R
    ax, ay, bx, by, cx, cy, dx, dy, p, q, r = map(float, sys.stdin.buffer.read().split())
    A, B, C, D = (ax, ay), (bx, by), (cx, cy), (dx, dy)
    P, Q, R = p, q, r
    print(f"{minimum_time():.2f}")


if __name__ == "__main__":
    solve()
