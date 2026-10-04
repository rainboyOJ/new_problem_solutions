#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 14:45
# update_at: 2026-09-30 14:45

import sys
from collections import deque

INF = 10**9


def min_cost_edges(graph: list[list[tuple[int, int]]], threshold: int, n: int) -> int:
    """计算从 1 到 n 路径上边权大于 threshold 的最少边数（0-1 BFS）。"""
    dist = [INF] * (n + 1)
    dist[1] = 0
    dq = deque([1])

    while dq:
        u = dq.popleft()
        if u == n:
            break
        d = dist[u]
        for v, w in graph[u]:
            cost = 1 if w > threshold else 0
            if d + cost < dist[v]:
                dist[v] = d + cost
                if cost == 0:
                    dq.appendleft(v)
                else:
                    dq.append(v)

    return dist[n]


def solve() -> None:
    tokens = sys.stdin.buffer.read().split()
    if not tokens:
        return
    data = iter(map(int, tokens))

    n = next(data)
    p = next(data)
    k = next(data)

    graph: list[list[tuple[int, int]]] = [[] for _ in range(n + 1)]
    max_len = 0
    for _ in range(p):
        u, v, w = next(data), next(data), next(data)
        graph[u].append((v, w))
        graph[v].append((u, w))
        if w > max_len:
            max_len = w

    # 若 1 与 n 之间连通性不足，直接判 -1
    if min_cost_edges(graph, INF, n) == INF:
        print(-1)
        return

    # 二分寻找最小的阈值 mid，使得大于 mid 的边数 <= k
    low, high, ans = 0, max_len, max_len
    while low <= high:
        mid = (low + high) // 2
        if min_cost_edges(graph, mid, n) <= k:
            ans = mid
            high = mid - 1
        else:
            low = mid + 1

    print(ans)


if __name__ == "__main__":
    solve()
