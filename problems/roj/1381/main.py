#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import heapq
import sys


def solve() -> None:
    """堆优化 Dijkstra：求 1 到 n 的最短路，不可达输出 -1。"""
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    # 邻接表：每条无向边存两次
    adj: list[list[tuple[int, int]]] = [[] for _ in range(n + 1)]
    for _ in range(m):
        a, b, c = next(data), next(data), next(data)
        adj[a].append((b, c))  # a -> b
        adj[b].append((a, c))  # b -> a

    INF = float("inf")
    dist = [INF] * (n + 1)
    dist[1] = 0
    heap = [(0, 1)]  # (距离, 点)

    while heap:
        d, u = heapq.heappop(heap)
        if d > dist[u]:  # 过期堆元素，跳过
            continue
        if u == n:
            break  # 第一次弹出即最短，提前结束
        for v, w in adj[u]:
            if d + w < dist[v]:
                dist[v] = d + w
                heapq.heappush(heap, (d + w, v))

    print(dist[n] if dist[n] < INF else -1)


if __name__ == "__main__":
    solve()
