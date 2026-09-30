#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 14:14
# update_at: 2026-09-30 14:14

import heapq
import sys

MOD = (1 << 31) - 1
INF = float("inf")


def dijkstra(n: int, adj: list[list[tuple[int, int]]]) -> list[int]:
    """计算源点 1 到各房间的最短距离列表（1-indexed）。"""
    dist = [INF] * (n + 1)
    dist[1] = 0
    pq = [(0, 1)]

    while pq:
        d, u = heapq.heappop(pq)
        if d > dist[u]:
            continue
        for v, w in adj[u]:
            if dist[u] + w < dist[v]:
                dist[v] = dist[u] + w
                heapq.heappush(pq, (dist[v], v))

    return dist


def count_parent_choices(u: int, adj: list[list[tuple[int, int]]], dist: list[int]) -> int:
    """统计房间 u 可选的树上前驱父节点数量。"""
    return sum(1 for v, w in adj[u] if dist[v] + w == dist[u])


def count_shortest_path_trees(n: int, adj: list[list[tuple[int, int]]]) -> int:
    """按乘法原理计算合法的最短路径生成树方案数。"""
    dist = dijkstra(n, adj)
    ans = 1
    for u in range(2, n + 1):
        choices = count_parent_choices(u, adj, dist)
        ans = (ans * choices) % MOD
    return ans


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data, None)
    if n is None:
        return
    m = next(data)

    adj: list[list[tuple[int, int]]] = [[] for _ in range(n + 1)]
    for _ in range(m):
        u, v, w = next(data), next(data), next(data)
        adj[u].append((v, w))
        adj[v].append((u, w))

    ans = count_shortest_path_trees(n, adj)
    print(ans)


if __name__ == "__main__":
    solve()
