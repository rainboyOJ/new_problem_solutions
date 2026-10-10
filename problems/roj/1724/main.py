#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 18:40
# update_at: 2026-10-07 18:40

import sys
from collections import deque
from collections.abc import Iterator

INF = 10**18  # 最短路初值哨兵，远大于任何约束路径和（c ≤ 1e4，边数 ≤ 3e4）

type Edge = tuple[int, int, int]  # (起点, 终点, 边权)：一条化好的约束边


def build_edges(data: Iterator[int], m: int) -> list[Edge]:
    """把 m 条记忆逐条化成差分约束的边 x_v <= x_u + w。"""
    edges: list[Edge] = []
    for _ in range(m):
        op = next(data)
        a, b = next(data), next(data)
        if op == 1:                       # a 至少比 b 多 c：x_b <= x_a - c
            c = next(data)
            edges.append((a, b, -c))
        elif op == 2:                     # a 至多比 b 多 c：x_a <= x_b + c
            c = next(data)
            edges.append((b, a, c))
        else:                             # a 与 b 一样多：双向各一条 0 权边
            edges.append((a, b, 0))
            edges.append((b, a, 0))
    return edges


def has_negative_cycle(edges: list[Edge], n: int) -> bool:
    """SPFA 从超级源点判负环：某点入队次数超过点数（含源点）即存在负环。"""
    # 超级源点 0 连向每个农场（权 0）：图不连通也能一次判完整
    edges = edges + [(0, i, 0) for i in range(1, n + 1)]
    adj: list[list[tuple[int, int]]] = [[] for _ in range(n + 1)]  # 邻接表 adj[u] = [(v, w)]
    for u, v, w in edges:
        adj[u].append((v, w))

    dist = [INF] * (n + 1)
    enq_cnt = [0] * (n + 1)   # 累计入队次数，Bellman-Ford 队列法的负环判据
    in_queue = [False] * (n + 1)
    dist[0] = 0
    queue = deque([0])
    in_queue[0] = True
    enq_cnt[0] = 1

    total_nodes = n + 1  # 农场 1..n 再加超级源点 0
    while queue:
        u = queue.popleft()
        in_queue[u] = False
        for v, w in adj[u]:
            if dist[u] + w < dist[v]:
                dist[v] = dist[u] + w
                if not in_queue[v]:
                    enq_cnt[v] += 1
                    if enq_cnt[v] > total_nodes:
                        return True
                    queue.append(v)
                    in_queue[v] = True
    return False


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    edges = build_edges(data, m)
    print("No" if has_negative_cycle(edges, n) else "Yes")


if __name__ == "__main__":
    solve()
