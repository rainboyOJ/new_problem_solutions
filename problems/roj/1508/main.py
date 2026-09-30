#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-03-31 09:00
# update_at: 2026-03-31 09:00

import sys
from collections import deque

INF = 10**18  # 无穷大哨兵


def has_negative_cycle(n: int, adj: list[list[tuple[int, int]]]) -> bool:
    """SPFA 检查全图是否存在负权环：将所有点入队松弛，松弛边数达到 n 则存在负权环。"""
    dist = [0] * (n + 1)
    edge_cnt = [0] * (n + 1)
    in_queue = [True] * (n + 1)
    queue: deque[int] = deque(range(1, n + 1))

    while queue:
        u = queue.popleft()
        in_queue[u] = False
        for v, weight in adj[u]:
            if dist[u] + weight < dist[v]:
                dist[v] = dist[u] + weight
                edge_cnt[v] = edge_cnt[u] + 1
                if edge_cnt[v] >= n:
                    return True
                if not in_queue[v]:
                    queue.append(v)
                    in_queue[v] = True
    return False


def shortest_paths(n: int, start: int, adj: list[list[tuple[int, int]]]) -> list[int]:
    """SPFA 求源点 start 到各点的单源最短路长度。"""
    dist = [INF] * (n + 1)
    dist[start] = 0
    in_queue = [False] * (n + 1)
    in_queue[start] = True
    queue: deque[int] = deque([start])

    while queue:
        u = queue.popleft()
        in_queue[u] = False
        for v, weight in adj[u]:
            if dist[u] + weight < dist[v]:
                dist[v] = dist[u] + weight
                if not in_queue[v]:
                    queue.append(v)
                    in_queue[v] = True
    return dist


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    try:
        token = next(data)
    except StopIteration:
        return
    n = int(token)
    m = int(next(data))
    start_node = int(next(data))

    adj: list[list[tuple[int, int]]] = [[] for _ in range(n + 1)]
    for _ in range(m):
        u, v, weight = int(next(data)), int(next(data)), int(next(data))
        adj[u].append((v, weight))

    if has_negative_cycle(n, adj):
        print("-1")
        return

    dist = shortest_paths(n, start_node, adj)
    out: list[str] = [
        "0" if i == start_node else ("NoPath" if dist[i] == INF else str(dist[i]))
        for i in range(1, n + 1)
    ]
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
