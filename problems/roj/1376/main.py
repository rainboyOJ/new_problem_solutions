#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 07:45
# update_at: 2026-09-30 07:45

import sys
from collections import defaultdict
from heapq import heappop, heappush


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)  # n 个哨所，m 条通信线路（无向边）

    adj: dict[int, list[tuple[int, int]]] = defaultdict(list)
    for _ in range(m):
        u, v, w = next(data), next(data), next(data)
        adj[u].append((v, w))  # 无向边两个方向都要登记
        adj[v].append((u, w))

    # Dijkstra：dist[t] = 命令从哨所 1 传到哨所 t 的最短天数
    INF = float('inf')
    dist = [INF] * (n + 1)
    dist[1] = 0
    heap = [(0, 1)]
    while heap:
        d, u = heappop(heap)
        if d > dist[u]:
            continue                        # 过期堆项，早已被更短路覆盖
        for v, w in adj[u]:
            nd = d + w
            if nd < dist[v]:
                dist[v] = nd
                heappush(heap, (nd, v))

    all_reached = all(d < INF for d in dist[1:])  # 哨所 1 自身必可达
    ans = max(dist[1:]) if all_reached else -1
    print(ans)


if __name__ == "__main__":
    solve()
