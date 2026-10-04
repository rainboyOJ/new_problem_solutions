#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 14:40
# update_at: 2026-09-30 14:40

import heapq
import sys

INF = 10**18


def dijkstra(n: int, start: int, adj: list[list[tuple[int, int]]]) -> list[int]:
    """计算从 start 出发到图中所有点的单源最短路距离。"""
    dist = [INF] * (n + 1)
    dist[start] = 0
    pq = [(0, start)]

    while pq:
        d, u = heapq.heappop(pq)
        if d > dist[u]:
            continue
        for v, w in adj[u]:
            if dist[u] + w < dist[v]:
                dist[v] = dist[u] + w
                heapq.heappush(pq, (dist[v], v))

    return dist


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m, x = next(data), next(data), next(data)

    adj: list[list[tuple[int, int]]] = [[] for _ in range(n + 1)]
    rev_adj: list[list[tuple[int, int]]] = [[] for _ in range(n + 1)]

    for _ in range(m):
        u, v, w = next(data), next(data), next(data)
        adj[u].append((v, w))
        rev_adj[v].append((u, w))

    dist_from_x = dijkstra(n, x, adj)
    dist_to_x = dijkstra(n, x, rev_adj)

    ans = max(dist_to_x[i] + dist_from_x[i] for i in range(1, n + 1))
    print(ans)


if __name__ == "__main__":
    solve()
