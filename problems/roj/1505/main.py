#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import heapq
import sys

INF = 10**9
MAX_COST = 10000


def solve() -> None:
    data = sys.stdin.read().split()
    if not data:
        return
    it = iter(map(int, data))
    n, m, s, e = next(it), next(it), next(it), next(it)

    adj: list[list[tuple[int, int, int]]] = [[] for _ in range(n + 1)]
    for _ in range(m):
        u, v, c, t = next(it), next(it), next(it), next(it)
        adj[u].append((v, c, t))
        adj[v].append((u, c, t))

    # dist[u][cost]: 到达节点 u 恰好花费 cost 时的最小时间
    dist = [[INF] * (MAX_COST + 1) for _ in range(n + 1)]
    dist[s][0] = 0
    pq: list[tuple[int, int, int]] = [(0, 0, s)]  # (time, cost, u)

    while pq:
        t, c, u = heapq.heappop(pq)
        if t > dist[u][c]:
            continue
        for v, edge_c, edge_t in adj[u]:
            nc, nt = c + edge_c, t + edge_t
            if nc <= MAX_COST and nt < dist[v][nc]:
                dist[v][nc] = nt
                heapq.heappush(pq, (nt, nc, v))

    # 统计帕累托最优解：按 cost 从小到大扫描，只有 time 严格小于当前历史最小 time 才是非支配解
    min_time = INF
    ans = 0
    for c in range(MAX_COST + 1):
        t = dist[e][c]
        if t < min_time:
            min_time = t
            ans += 1

    print(ans)


if __name__ == "__main__":
    solve()
