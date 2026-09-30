#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 10:00
# update_at: 2026-09-29 10:00

import heapq
import sys
from collections import Counter

INF = 10**30  # 不可达哨兵


def dijkstra(start: int, adj: list[list[tuple[int, int]]]) -> list[int]:
    """从 start 出发到每个牧场的最短路（堆优化 Dijkstra）。"""
    dist = [INF] * len(adj)
    dist[start] = 0
    heap = [(0, start)]
    while heap:
        d, u = heapq.heappop(heap)
        if d > dist[u]:  # 过期堆项：u 已被更短的路径更新过
            continue
        for v, w in adj[u]:
            nd = d + w
            if nd < dist[v]:
                dist[v] = nd
                heapq.heappush(heap, (nd, v))
    return dist


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, p, c = next(data), next(data), next(data)

    # 同一牧场可能有多头牛，按头数计数，求和时乘上权重
    cow_cnt = Counter(next(data) for _ in range(n))

    # 邻接表，双向边
    adj: list[list[tuple[int, int]]] = [[] for _ in range(p + 1)]
    for _ in range(c):
        a, b, w = next(data), next(data), next(data)
        adj[a].append((b, w))  # 双向边
        adj[b].append((a, w))

    # 糖可以放在任意牧场（含没有牛的），从每个牧场各跑一次 Dijkstra，取所有牛路程和的最小值
    print(min(
        sum(cnt * dist[pasture] for pasture, cnt in cow_cnt.items())
        for dist in (dijkstra(src, adj) for src in range(1, p + 1))
    ))


if __name__ == "__main__":
    solve()
