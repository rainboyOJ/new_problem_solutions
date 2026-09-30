#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-04-18 10:00
# update_at: 2026-04-18 10:00

import heapq
import itertools
import sys

INF = 10**18


def dijkstra(n: int, adj: list[list[tuple[int, int]]], start: int) -> list[int]:
    """计算从源点 start 出发到达所有顶点的单源最短路距离数组。"""
    dist = [INF] * (n + 1)
    dist[start] = 0
    pq = [(0, start)]

    while pq:
        d, u = heapq.heappop(pq)
        if d > dist[u]:
            continue
        for v, w in adj[u]:
            new_d = d + w
            if new_d < dist[v]:
                dist[v] = new_d
                heapq.heappush(pq, (new_d, v))

    return dist


def min_visit_time(key_nodes: list[int], dist_map: list[list[int]]) -> int:
    """枚举拜访 5 个亲戚的所有排列顺序，计算从家 (0) 出发拜访全部亲戚的最短总时间。"""
    return min(
        dist_map[0][order[0]]
        + sum(dist_map[order[i]][order[i + 1]] for i in range(4))
        for order in itertools.permutations(range(1, 6))
    )


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    try:
        n_token = next(data)
    except StopIteration:
        return
    n, m = int(n_token), int(next(data))
    relatives = [int(next(data)) for _ in range(5)]

    adj: list[list[tuple[int, int]]] = [[] for _ in range(n + 1)]
    for _ in range(m):
        u = int(next(data))
        v = int(next(data))
        w = int(next(data))
        adj[u].append((v, w))
        adj[v].append((u, w))

    # 关键节点：0 号为佳佳家（车站 1），1..5 号为五个亲戚所在车站
    key_nodes = [1] + relatives
    all_dist = [dijkstra(n, adj, s) for s in key_nodes]
    dist_map = [[all_dist[i][key_nodes[j]] for j in range(6)] for i in range(6)]

    ans = min_visit_time(key_nodes, dist_map)
    print(ans)


if __name__ == "__main__":
    solve()
