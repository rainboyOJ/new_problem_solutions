#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 06:55
# update_at: 2026-10-01 06:55

import sys
from fractions import Fraction

Point = tuple[int, int]


def cross(o: Point, a: Point, b: Point) -> int:
    """oa × ob：>0 左转，<0 右转，=0 三点共线。"""
    return (a[0] - o[0]) * (b[1] - o[1]) - (a[1] - o[1]) * (b[0] - o[0])


def on_segment(p: Point, a: Point, b: Point) -> bool:
    """已知三点共线时，p 是否落在 ab 线段上（含端点）。"""
    return (min(a[0], b[0]) <= p[0] <= max(a[0], b[0])
            and min(a[1], b[1]) <= p[1] <= max(a[1], b[1]))


def touches(p1: Point, p2: Point, q1: Point, q2: Point) -> bool:
    """两条线段是否有公共点：严格跨立，或端点落在对方线段上（含共线重叠）。"""
    d1, d2 = cross(p1, p2, q1), cross(p1, p2, q2)
    d3, d4 = cross(q1, q2, p1), cross(q1, q2, p2)
    if d1 * d2 < 0 and d3 * d4 < 0:
        return True
    return (d1 == 0 and on_segment(q1, p1, p2)
            or d2 == 0 and on_segment(q2, p1, p2)
            or d3 == 0 and on_segment(p1, q1, q2)
            or d4 == 0 and on_segment(p2, q1, q2))


def is_simple(pts: list[Point]) -> bool:
    """合法闭合栅栏：任意两条栅栏除公共顶点外没有别的交点（不自交、不重叠）。"""
    n = len(pts)
    for i in range(n):
        a1, a2 = pts[i], pts[(i + 1) % n]
        for j in range(i + 1, n):
            b1, b2 = pts[j], pts[(j + 1) % n]
            adjacent = j == i + 1 or (i == 0 and j == n - 1)
            if not adjacent:
                if touches(a1, a2, b1, b2):
                    return False
                continue
            # 相邻栅栏天然交于公共顶点；只有当两者共线且在该顶点之外还互相覆盖才不合法
            shared, pa, pb = (a2, a1, b2) if j == i + 1 else (a1, a2, b1)
            if cross(shared, pa, pb) == 0 and (
                    on_segment(pb, shared, pa) or on_segment(pa, shared, pb)):
                return False
    return True


def visible(i: int, pts: list[Point], obs: Point) -> bool:
    """栅栏 i（pts[i]→pts[i+1]）是否可被观察者看到：段上存在一个不被遮挡的点。"""
    n = len(pts)
    a1, a2 = pts[i], pts[(i + 1) % n]
    ox, oy = obs
    if cross(a1, a2, obs) == 0:
        return False  # 观察者与栅栏共线，目光沿栅栏方向，按题意不算可见
    ux, uy = a2[0] - a1[0], a2[1] - a1[1]

    # obs→各顶点的直线把 AB 分成若干开段，段内"被谁挡住"不变，只需测每段中点
    cuts = {Fraction(0), Fraction(1)}
    for cx, cy in pts:
        ex, ey = cx - ox, cy - oy
        den = ex * uy - ey * ux  # 交点参数分母 cross(e, U)，=0 即与 AB 平行
        if den == 0:
            continue
        num = ey * (a1[0] - ox) - ex * (a1[1] - oy)  # 参数分子 -cross(e, A-obs)
        if den < 0:
            num, den = -num, -den
        if 0 < num < den:  # 交点确实落在线段 AB 内部
            cuts.add(Fraction(num, den))

    # 其余栅栏的跨立判据预计算：相对观察者的位移、方向 c、观察者所在侧
    others = []
    for k in range(n):
        if k == i:
            continue
        q1, q2 = pts[k], pts[(k + 1) % n]
        cx, cy = q2[0] - q1[0], q2[1] - q1[1]
        side = cx * (oy - q1[1]) - cy * (ox - q1[0])  # cross(c, obs-q1)
        others.append((q1[0] - ox, q1[1] - oy,
                       q2[0] - ox, q2[1] - oy, cx, cy, side))

    seq = sorted(cuts)
    for lo, hi in zip(seq, seq[1:]):
        mid = (lo + hi) / 2
        den = mid.denominator
        # 中点方向向量 (P-obs)·den：P = A + mid·U，全程整数避免浮点误差
        vx = (a1[0] - ox) * den + mid.numerator * ux
        vy = (a1[1] - oy) * den + mid.numerator * uy
        blocked = False
        for r1x, r1y, r2x, r2y, cx, cy, side in others:
            t1 = vx * r1y - vy * r1x          # cross(P-obs, q1-obs)
            t2 = vx * r2y - vy * r2x          # cross(P-obs, q2-obs)
            if t1 == 0 or t2 == 0 or (t1 ^ t2) >= 0:
                continue                      # 观察者两端不在对方直线两侧，非跨立
            # cross(c, P-q1) 的符号 = cross(c, P-obs) + den·side 的符号
            u = cx * vy - cy * vx + den * side
            if side != 0 and u != 0 and (side ^ u) < 0:
                blocked = True                # 视线严格穿过该栅栏，被它挡住
                break
        if not blocked:
            return True
    return False


def solve() -> None:
    lines = sys.stdin.read().splitlines()
    n = int(lines[0])
    head = lines[1].split()
    obs = (int(head[0]), int(head[1]))

    # 顶点逐行读取：一行给出 (x, y)；若该行只有一个数，则与下一行首数合成一个顶点
    pts: list[Point] = []
    row = 2
    while len(pts) < n:
        toks = lines[row].split()
        if len(toks) > 1:
            pts.append((int(toks[0]), int(toks[1])))
            row += 1
        else:
            pts.append((int(toks[0]), int(lines[row + 1].split()[0])))
            row += 2

    if not is_simple(pts):
        print("NOFENCE")
        return

    seen = [i for i in range(n) if visible(i, pts, obs)]
    # 按"最后一个点"（输入序号大者）排序，相同时再按"第一个点"排序
    seen.sort(key=lambda i: (max(i, (i + 1) % n), min(i, (i + 1) % n)))

    out = [str(len(seen))]
    for i in seen:
        j = (i + 1) % n
        first, last = (pts[i], pts[j]) if i < j else (pts[j], pts[i])
        out.append(f"{first[0]} {first[1]} {last[0]} {last[1]}")
    print("\n".join(out))


if __name__ == "__main__":
    solve()
