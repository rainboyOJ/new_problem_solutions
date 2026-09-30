#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 07:08
# update_at: 2026-10-01 07:08

import sys
from itertools import pairwise
from math import hypot

Scalar = int | float
Point = tuple[Scalar, Scalar]


def cross(o: Point, a: Point, b: Point) -> Scalar:
    """叉积 (a - o) × (b - o)：> 0 表示 o→a→b 左转，= 0 表示三点共线。"""
    return (a[0] - o[0]) * (b[1] - o[1]) - (a[1] - o[1]) * (b[0] - o[0])


def convex_hull(points: list[Point]) -> list[Point]:
    """单调链求凸包：返回逆时针顶点序列，边上的共线点只保留线段两端。

    先按 (x, y) 升序排序，于是"最左点取最下、最右点取最上"；
    新点不能与栈顶构成左转时，栈顶就不可能是凸包顶点，弹掉。
    """
    ordered = sorted(points)
    lower: list[Point] = []                     # 左下 → 右上的下凸壳
    for p in ordered:
        while len(lower) >= 2:
            if cross(lower[-2], lower[-1], p) > 0:
                break                           # 左转：栈顶仍是凸壳顶点
            lower.pop()                         # 右转或共线：栈顶多余
        lower.append(p)
    upper: list[Point] = []                     # 右上 → 左下的上凸壳
    for p in reversed(ordered):
        while len(upper) >= 2:
            if cross(upper[-2], upper[-1], p) > 0:
                break
            upper.pop()
        upper.append(p)
    return lower[:-1] + upper[:-1]              # 首尾两点在两条链里各出现一次


def perimeter(points: list[Point]) -> float:
    """正解：围住一个点集的最短闭合曲线就是它的凸包，答案即凸包周长。

    退化为凸包只有 1 个点时周长自然是 0；只剩 2 个端点（点全共线）时，
    "走个来回"是最短的闭合曲线，周长同样由闭合折线公式自然算出。
    """
    ring = convex_hull(points)                  # 逆时针凸包顶点序列
    # ring[:1] 把首顶点复制到末尾，这样 pairwise 也会算出闭合边
    return sum(hypot(q[0] - p[0], q[1] - p[1]) for p, q in pairwise(ring + ring[:1]))


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n = int(next(data))
    points: list[Point] = [(float(next(data)), float(next(data))) for _ in range(n)]
    print(f"{perimeter(points):.2f}")


if __name__ == "__main__":
    solve()
