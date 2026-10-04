#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-04-18 10:00
# update_at: 2026-04-18 10:00

import sys

INF = 10**18


def prim_mst(n: int, adj: list[list[int]]) -> int:
    """计算稠密图的最小生成树边权和。"""
    min_cost = [INF] * n
    min_cost[0] = 0
    visited = [False] * n

    for _ in range(n):
        # 挑选当前未加入树且到树距离最小的农场
        u = min((v for v in range(n) if not visited[v]), key=lambda v: min_cost[v])
        visited[u] = True
        for v in range(n):
            if not visited[v] and adj[u][v] < min_cost[v]:
                min_cost[v] = adj[u][v]

    return sum(min_cost)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    adj = [[next(data) for _ in range(n)] for _ in range(n)]
    print(prim_mst(n, adj))


if __name__ == "__main__":
    solve()
