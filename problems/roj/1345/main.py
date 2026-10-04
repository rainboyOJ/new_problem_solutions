#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 06:22
# update_at: 2026-09-30 06:22

import sys
from collections import Counter
from heapq import heappop, heappush

UNREACHABLE = -1  # 某源点到某牧场的距离为无穷大时的占位（不可达标记）


def dijkstra(src: int, adj: list[list[tuple[int, int]]]) -> list[int]:
    """单源最短路：(src 到每个牧场的最短距离)，不可达记 UNREACHABLE。"""
    dist = [UNREACHABLE] * len(adj)
    dist[src] = 0
    heap = [(0, src)]
    while heap:
        d, u = heappop(heap)
        if d > dist[u]:     # 堆里的过期条目：已经有更短的距离定型了
            continue
        for v, w in adj[u]:
            nd = d + w
            if dist[v] == UNREACHABLE or nd < dist[v]:
                dist[v] = nd
                heappush(heap, (nd, v))
    return dist


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, p, c = next(data), next(data), next(data)
    cows = [next(data) for _ in range(n)]           # 每头牛所在的牧场

    adj: list[list[tuple[int, int]]] = [[] for _ in range(p + 1)]  # 下标 1..p 是牧场
    for _ in range(c):
        a, b, w = next(data), next(data), next(data)
        adj[a].append((b, w))                       # 道路双向
        adj[b].append((a, w))

    head_count = Counter(cows)                      # 一个牧场可能站多头牛，按头数加权

    best = None
    for src in range(1, p + 1):
        dist = dijkstra(src, adj)
        # 有一头牛不可达，这个牧场就不合法：跳过，别让"无穷大"混进求和
        reachable = all(dist[x] != UNREACHABLE for x in head_count)
        if not reachable:
            continue
        total = sum(cnt * dist[x] for x, cnt in head_count.items())
        if best is None or total < best:
            best = total

    print(best)


if __name__ == "__main__":
    solve()
