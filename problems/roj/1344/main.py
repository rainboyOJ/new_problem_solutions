#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 06:08
# update_at: 2026-09-30 06:08

import sys
from heapq import heappop, heappush


def dijkstra(adj: list[list[tuple[int, float]]], start: int) -> list[float]:
    """从 start 出发到每个点的“最少放大倍数”：边权是 >1 的乘法因子。"""
    dist = [float("inf")] * len(adj)
    dist[start] = 1.0                        # 不转账金额不变，起点的倍数为 1
    heap = [(1.0, start)]
    while heap:
        factor, u = heappop(heap)
        if factor > dist[u]:                # 过期堆元素，早已被更小倍数覆盖
            continue
        for v, w in adj[u]:
            relaxed = factor * w            # 再过一条手续费 z% 的边累计的倍数
            if relaxed < dist[v]:
                dist[v] = relaxed
                heappush(heap, (relaxed, v))
    return dist


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    adj: list[list[tuple[int, float]]] = [[] for _ in range(n + 1)]
    for _ in range(m):
        x, y, z = next(data), next(data), next(data)
        # 手续费扣 z%：寄出 100/(100-z) 元对方才到账 100 元，故边权是这个比值
        adj[x].append((y, 100 / (100 - z)))
        adj[y].append((x, 100 / (100 - z)))

    A, B = next(data), next(data)
    dist = dijkstra(adj, A)
    print(f"{dist[B] * 100:.8f}")            # B 到手 100 元，A 至少出 倍数×100


if __name__ == "__main__":
    solve()
