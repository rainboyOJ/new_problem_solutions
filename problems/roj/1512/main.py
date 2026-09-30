#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 15:31
# update_at: 2026-09-30 15:31

import sys
from collections import deque

INF = 10**18


def spfa(n: int, adj: list[list[tuple[int, int]]], source: int | None) -> tuple[bool, list[int]]:
    """用 SPFA 求从源点出发的最短路并检测负环。

    若 source 为 None，则初始将所有点入队（等价于建立超级源点向各点连边权 0 的边），
    用于全局判负环。
    返回 (has_negative_cycle, dist)。
    """
    dist = [0 if source is None else INF] * (n + 1)
    in_queue = [True if source is None else False] * (n + 1)
    count = [0] * (n + 1)
    queue = deque(range(1, n + 1) if source is None else [source])

    if source is not None:
        dist[source] = 0
        in_queue[source] = True

    while queue:
        u = queue.popleft()
        in_queue[u] = False
        d_u = dist[u]

        for v, w in adj[u]:
            cand = d_u + w
            if cand < dist[v]:
                dist[v] = cand
                if not in_queue[v]:
                    count[v] += 1
                    if count[v] >= n:
                        return True, dist
                    in_queue[v] = True
                    queue.append(v)

    return False, dist


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    tokens = list(data)
    if not tokens:
        return
    it = iter(tokens)
    n, ml, md = next(it), next(it), next(it)

    # 建图：adj[u] 存储出边 (v, w)，表示不等式 dist[v] <= dist[u] + w
    adj: list[list[tuple[int, int]]] = [[] for _ in range(n + 1)]

    # 1. 相对顺序限制：x[i] <= x[i+1] => x[i] - x[i+1] <= 0 => 从 i+1 到 i 连边权 0
    for i in range(1, n):
        adj[i + 1].append((i, 0))

    # 2. 友好关系：x[b] - x[a] <= d (a < b) => 从 a 到 b 连边权 d
    for _ in range(ml):
        a, b, d = next(it), next(it), next(it)
        if a > b:
            a, b = b, a
        adj[a].append((b, d))

    # 3. 反感关系：x[b] - x[a] >= d (a < b) => x[a] - x[b] <= -d => 从 b 到 a 连边权 -d
    for _ in range(md):
        a, b, d = next(it), next(it), next(it)
        if a > b:
            a, b = b, a
        adj[b].append((a, -d))

    # 第一阶段：全局负环检测（无解判定）
    has_neg_cycle, _ = spfa(n, adj, None)
    if has_neg_cycle:
        print(-1)
        return

    # 第二阶段：以 1 号牛为起点求单源最短路
    _, dist = spfa(n, adj, 1)
    if dist[n] == INF:
        print(-2)
    else:
        print(dist[n])


if __name__ == "__main__":
    solve()
