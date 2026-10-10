#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 17:51
# update_at: 2026-10-07 17:51

import sys
from bisect import bisect_right

type Point = tuple[int, int]    # 一棵生成树的两个代价分量 (Σu, Σv)
type Edges = list[tuple[int, int, int, int]]   # 每条边的 (x, y, u, v)


def mst(edges: Edges, n: int, d1: int, d2: int) -> Point:
    """以 d1·u + d2·v 为边权做 Kruskal，返回该生成树的 (Σu, Σv)。"""
    parent = list(range(n + 1))

    def find(x: int) -> int:
        """并查集找根，路径压缩。"""
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

    su = sv = 0
    cnt = 0
    # 同权时按 (u, v) 升序，保证方向 (1,0) / (0,1) 取到的是凸壳端点而不是被支配点
    for x, y, u, v in sorted(edges, key=lambda e: (d1 * e[2] + d2 * e[3], e[2], e[3])):
        rx, ry = find(x), find(y)
        if rx != ry:
            parent[rx] = ry
            su += u
            sv += v
            cnt += 1
            if cnt == n - 1:   # 生成树已满，剩下的边不必再看
                break
    return su, sv


def hull_points(edges: Edges, n: int) -> list[Point]:
    """全部生成树点的左下（Pareto 最小）凸壳，按 Σu 升序返回。"""
    left, right = mst(edges, n, 1, 0), mst(edges, n, 0, 1)
    pts, stack = [left, right], [(left, right)]
    while stack:
        (la, lb), (ra, rb) = stack.pop()
        if la >= ra:                                   # a 区间已空
            continue
        mid = mst(edges, n, lb - rb, ra - la)          # 沿弦的法向求 MST
        # 叉积 (r-l)×(mid-l)：< 0 说明 mid 严格落在弦下方，是新的凸壳顶点
        if (ra - la) * (mid[1] - lb) - (rb - lb) * (mid[0] - la) < 0 and la < mid[0] < ra:
            pts.append(mid)
            stack += [((la, lb), mid), (mid, (ra, rb))]
    chain: list[Point] = []
    for p in sorted(set(pts)):                         # 去重后只留 b 严格递减的点
        if not chain or p[1] < chain[-1][1]:
            chain.append(p)
    return chain


def solve() -> None:
    n, m, q = map(int, sys.stdin.buffer.readline().split())
    edges: Edges = [tuple(map(int, sys.stdin.buffer.readline().split())) for _ in range(m)]
    chain = hull_points(edges, n)

    # 相邻凸壳点的分界斜率 r_i = (b_i - b_{i+1}) / (a_{i+1} - a_i)，随 i 严格递减；
    # 询问 (k1,k2) 的最优点就是第一个满足 r_i <= k1/k2 的点，故倒序排成升序后二分定位。
    cuts = sorted((b1 - b2) / (a2 - a1) for (a1, b1), (a2, b2) in zip(chain, chain[1:]))
    vals = iter(map(float, sys.stdin.buffer.read().split()))
    out = []
    for k1, k2 in zip(vals, vals):                     # 每个询问两个实数：k1 k2
        a, b = chain[len(cuts) - bisect_right(cuts, k1 / k2)]
        out.append(f"{k1 * a + k2 * b:.3f}")
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
