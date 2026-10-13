#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-13 17:08
# update_at: 2026-10-13 17:08
#
# 邻接表 + 堆优化 Dijkstra 单源最短路：本题只问 s 到 t 一条距离。
# 点编号 1..n，g[u] 存 u 的出边 (终点 v, 边权 w)，无向边两个方向各存一次。
# 边权是两点间欧氏距离，恒为非负，所以每个点出堆时它的最短路已确定，不会再变。
# C++ 的 long long 与 1e100 在这里是 Python int / float，任意精度，不会溢出。

import sys
from heapq import heappop, heappush
from math import hypot

INF = float("inf")  # 不可达哨兵

type WeightedAdj = list[list[tuple[int, float]]]
type Seq = list[float]


def dijkstra(n: int, g: WeightedAdj, source: int, target: int) -> float:
    """返回 source 到 target 的最短路；不可达返回 INF。"""
    dist: Seq = [INF] * (n + 1)
    done = [False] * (n + 1)  # done[u] 为真表示 u 已出堆，最短路已确定
    dist[source] = 0

    # 小根堆放 (当前距离, 点编号)，保证每次取出未确定点里距离最小的那个
    pq: list[tuple[float, int]] = [(0.0, source)]
    while pq:
        d, u = heappop(pq)
        if done[u]:
            continue  # 同一个点可能进堆多次，只有第一次有用
        done[u] = True
        if u == target:
            break  # 只问 s 到 t，t 确定了就可以停

        for v, w in g[u]:
            whole = d + w
            if whole < dist[v]:
                dist[v] = whole
                heappush(pq, (whole, v))  # 旧的 (dist, v) 留在堆里，靠 done 跳过

    return dist[target]


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n = int(next(data))
    xs: Seq = [0.0] * (n + 1)
    ys: Seq = [0.0] * (n + 1)
    for i in range(1, n + 1):  # 点的坐标，1 下标
        xs[i] = int(next(data))
        ys[i] = int(next(data))

    m = int(next(data))
    g: WeightedAdj = [[] for _ in range(n + 1)]
    for _ in range(m):
        u, v = int(next(data)), int(next(data))
        w = hypot(xs[u] - xs[v], ys[u] - ys[v])  # 连线长度 = 两点间直线距离
        g[u].append((v, w))
        g[v].append((u, w))  # 无向边：两个方向各存一次
    s, t = int(next(data)), int(next(data))

    print(f"{dijkstra(n, g, s, t):.2f}")


if __name__ == "__main__":
    solve()
