#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 18:43
# update_at: 2026-10-07 18:43

import sys
from heapq import heappop, heappush

INF = float("inf")
EPS_ABS = 1e-8   # 弦值比较的绝对容差，扛小量级距离上的浮点噪声
EPS_REL = 1e-11  # 相对容差，按距离量级放大（沿 <=200 条边累加，误差远小于它）
MAX_DEPTH = 50   # 细分深度上限，防止在浮点噪声处无限二分

type Adj = list[list[tuple[int, int, int]]]  # adj[u] = [(v, x, y)]，无向边两侧各存一份


def shortest(a: float, adj: Adj, s: int, t: int) -> float:
    """拥堵系数固定为 a 时 s->t 的最短路（堆优化 Dijkstra）。"""
    dist = {s: 0.0}
    heap = [(0.0, s)]
    while heap:
        d, u = heappop(heap)
        if u == t:
            return d                     # 终点出堆时距离已确定
        if d > dist.get(u, INF):
            continue                     # 堆里的过时记录
        for v, x, y in adj[u]:
            nd = d + a * x + (1.0 - a) * y
            if nd < dist.get(v, INF):
                dist[v] = nd
                heappush(heap, (nd, v))
    return dist.get(t, INF)


def integrate(lo: float, hi: float, flo: float, fhi: float,
              adj: Adj, s: int, t: int, depth: int = 0) -> float:
    """在 [lo,hi] 上积分 d(a)，已知两端值 flo=d(lo)、fhi=d(hi)。

    d(a) 是若干直线（每条路径代价 = Y_P + a*(X_P-Y_P)）的下包络，故在 [0,1] 上凹且
    分段线性。凹函数在区间中点的值一旦等于两端弦值，整段就贴合这条弦，可以直接按
    梯形算面积；否则区间内还有折点，二分继续细分。斜率是整数，折点两侧斜率差至少 1，
    每次细分间隙减半，所以深度有限（再用 MAX_DEPTH 兜底）。
    """
    mid = (lo + hi) * 0.5
    fm = shortest(mid, adj, s, t)
    chord = (flo + fhi) * 0.5            # 两端点连线在中点的高度
    eps = EPS_ABS + EPS_REL * max(abs(flo), abs(fhi), 1.0)
    if depth >= MAX_DEPTH or fm <= chord + eps:
        return chord * (hi - lo)         # 该段就是直线，梯形面积即精确值
    return (integrate(lo, mid, flo, fm, adj, s, t, depth + 1)
            + integrate(mid, hi, fm, fhi, adj, s, t, depth + 1))


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m, s, t = next(data), next(data), next(data), next(data)

    adj: Adj = [[] for _ in range(n + 1)]
    for _ in range(m):
        u, v, x, y = next(data), next(data), next(data), next(data)
        adj[u].append((v, x, y))         # 无向边：两个方向都放
        adj[v].append((u, x, y))

    f0 = shortest(0.0, adj, s, t)        # a=0：每条边取空闲耗时 y
    f1 = shortest(1.0, adj, s, t)        # a=1：每条边取最拥堵耗时 x
    ans = integrate(0.0, 1.0, f0, f1, adj, s, t)

    # 题面没规定精度，样例是 "2.5" / "13.0"：打印 10 位小数后去掉多余尾零（至少留一位）
    text = f"{ans:.10f}".rstrip("0")
    print(text + "0" if text.endswith(".") else text)


if __name__ == "__main__":
    solve()
