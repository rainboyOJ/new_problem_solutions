#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-04-18 10:00
# update_at: 2026-04-18 10:00

import sys
from functools import reduce
from operator import xor


def compute_sg(graph: list[list[int]], n: int) -> list[int]:
    """按拓扑逆序计算 DAG 上所有节点的 SG 值。"""
    in_degree = [0] * (n + 1)
    for u in range(1, n + 1):
        for v in graph[u]:
            in_degree[v] += 1

    queue = [u for u in range(1, n + 1) if in_degree[u] == 0]
    topo_order: list[int] = []
    for u in queue:
        topo_order.append(u)
        for v in graph[u]:
            in_degree[v] -= 1
            if in_degree[v] == 0:
                queue.append(v)

    sg = [0] * (n + 1)
    for u in reversed(topo_order):
        seen = {sg[v] for v in graph[u]}
        mex = 0
        while mex in seen:
            mex += 1
        sg[u] = mex

    return sg


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m, k = next(data), next(data), next(data)

    graph: list[list[int]] = [[] for _ in range(n + 1)]
    for _ in range(m):
        u, v = next(data), next(data)
        graph[u].append(v)

    pieces = [next(data) for _ in range(k)]

    sg = compute_sg(graph, n)
    nim_sum = reduce(xor, (sg[p] for p in pieces), 0)

    print("win" if nim_sum != 0 else "lose")


if __name__ == "__main__":
    solve()
