#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 08:00
# update_at: 2026-09-30 08:00

import sys
from heapq import heappop, heappush

INF = 1 << 60  # 距离哨兵：大于任何可能的最短路（最长不超过 n*w ≤ 1e5 * 1000）


def dijkstra(n: int, adj: list[list[tuple[int, int]]]) -> int:
    """返回 1 到 n 的最短距离：权值全为正，堆优化 Dijkstra 按距离从小到大敲定每个点。"""
    dist = [INF] * (n + 1)
    dist[1] = 0
    heap = [(0, 1)]  # (候选距离, 点)：堆顶是当前候选距离最小的点
    while heap:
        d, u = heappop(heap)
        if u == n:  # n 第一次出堆时它的候选距离已不可能再变小
            return d
        if d > dist[u]:  # 过期条目：u 后来又被更小的距离松弛过，跳过
            continue
        for v, w in adj[u]:
            nd = d + w
            if nd < dist[v]:
                dist[v] = nd
                heappush(heap, (nd, v))
    return dist[n]  # 题面保证 1 到 n 连通，正常运行到不了这里


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    adj: list[list[tuple[int, int]]] = [[] for _ in range(n + 1)]
    for _ in range(m):
        a, b, c = next(data), next(data), next(data)  # 无向边 a—b，长 c
        adj[a].append((b, c))
        adj[b].append((a, c))  # 重边、自环照常存，松弛时自然被淘汰

    print(dijkstra(n, adj))


if __name__ == "__main__":
    solve()
