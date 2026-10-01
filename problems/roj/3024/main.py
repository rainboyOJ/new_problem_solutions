#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 10:39
# update_at: 2026-10-01 10:39

import random
import sys
from operator import itemgetter

STATION = 0  # 颜色编码：0 = 核电站
AGENT = 1    # 颜色编码：1 = 特工
SAMPLE_K = 1000  # 开局随机抽多少对跨色点当初始上界


def dist_sq(p: tuple, q: tuple) -> int:
    """两点距离的平方：全程用整数比较，避免开方误差。"""
    dx = p[0] - q[0]
    dy = p[1] - q[1]
    return dx * dx + dy * dy


def merge_by_y(a: list, b: list) -> list:
    """归并两个已按 y 升序的列表，O(len(a)+len(b))。"""
    out = []
    i = j = 0
    while i < len(a) and j < len(b):
        if a[i][1] <= b[j][1]:
            out.append(a[i])
            i += 1
        else:
            out.append(b[j])
            j += 1
    return out + a[i:] + b[j:]


def divide(pts: list, best: int) -> tuple[int, list]:
    """分治：pts 已按 (x, y) 排序。

    返回 (跨色最小距离平方的当前上界 best, 该批点按 y 升序的列表)。
    best 一路当作"剪枝下限"传入传出：只会变小，不会漏掉更优的跨色点对。
    """
    n = len(pts)
    if n < 2:
        return best, pts
    mid = n // 2
    mid_x = pts[mid][0]  # 分割竖线：左半 x ≤ mid_x ≤ 右半 x

    best, left = divide(pts[:mid], best)
    best, right = divide(pts[mid:], best)
    by_y = merge_by_y(left, right)  # 两半各自已按 y 有序，归并免得重复排序

    # 更近的跨色点对 (l, r) 必有 l.x、r.x 都落在分割线附近：
    # 若 mid_x - l.x ≥ √best，则距离 ≥ r.x - l.x ≥ mid_x - l.x ≥ √best，不可能更优
    strip = [p for p in by_y if (p[0] - mid_x) ** 2 < best]

    # strip 已按 y 升序；q 在 p 之后且 y 己 ≥ √best 时，后面的点只会更远
    m = len(strip)
    for i in range(m):
        px, py, pc = strip[i]
        for j in range(i + 1, m):
            qx, qy, qc = strip[j]
            if (qy - py) ** 2 >= best:
                break
            if qc == pc:  # 同色点对（电站-电站 / 特工-特工）不计入答案
                continue
            best = min(best, dist_sq(strip[i], strip[j]))
    return best, by_y


def closest_pair(stations: list, agents: list) -> float:
    """返回任一电站到任一特工的最小欧氏距离。"""
    pts = [(x, y, STATION) for x, y in stations] + [(x, y, AGENT) for x, y in agents]
    pts.sort()

    # 先随机抽些跨色点对估个上界：让分治一开始就有有限的剪枝半径，
    # 也避免"整批点同色/跨色对很少"时 strip 内层循环失去 break 依据
    pairs = zip(random.choices(stations, k=SAMPLE_K), random.choices(agents, k=SAMPLE_K))
    best = min(dist_sq(p, q) for p, q in pairs)
    best, _ = divide(pts, best)
    return best ** 0.5


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)

    for _ in range(T):
        n = next(data)
        stations = [(next(data), next(data)) for _ in range(n)]
        agents = [(next(data), next(data)) for _ in range(n)]
        out.append(f"{closest_pair(stations, agents):.3f}")

    print("\n".join(out))


if __name__ == "__main__":
    solve()
