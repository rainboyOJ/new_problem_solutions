#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 07:55
# update_at: 2026-09-30 07:55

import sys
from heapq import heappop, heappush

INF = 1 << 60  # 比任何可行路径都大的哨兵：最大费用和 6200 * 1000 远小于它


def dijkstra(adj: list[list[tuple[int, int]]], start: int, goal: int) -> int:
    """在非负权无向图上求 start 到 goal 的最短距离；图连通，必然可达。"""
    dist = [INF] * len(adj)
    dist[start] = 0
    heap: list[tuple[int, int]] = [(0, start)]  # 小根堆里存 (当前距离, 点)，惰性删除过期项

    while heap:
        d, u = heappop(heap)
        if d != dist[u]:
            continue  # 堆里的旧版本，u 已经被更小的 d 松弛过
        if u == goal:
            return d  # 出堆即定型：非负权下第一次弹出 goal 就是最短距离
        for v, w in adj[u]:
            nd = d + w
            if nd < dist[v]:
                dist[v] = nd
                heappush(heap, (nd, v))

    return dist[goal]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    town_count = next(data)
    road_count = next(data)
    start = next(data)
    goal = next(data)

    adj: list[list[tuple[int, int]]] = [[] for _ in range(town_count + 1)]
    for _ in range(road_count):
        rs, re, cost = next(data), next(data), next(data)
        adj[rs].append((re, cost))  # 道路双向，两个方向各存一条
        adj[re].append((rs, cost))

    print(dijkstra(adj, start, goal))


if __name__ == "__main__":
    solve()
