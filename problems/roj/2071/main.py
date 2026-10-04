#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys
from collections import deque


def reachable_nodes(graph: list[list[int]], start: int, blocked: int | None = None) -> set[int]:
    """求从 start 出发、不经过 blocked 点所能到达的所有点集合。"""
    visited = {start}
    queue = deque([start])
    while queue:
        u = queue.popleft()
        for v in graph[u]:
            if v != blocked and v not in visited:
                visited.add(v)
                queue.append(v)
    return visited


def solve() -> None:
    data = sys.stdin.read().split()
    if not data:
        return
    it = iter(data)

    # 构图：第 i 行以 -2 结尾，最后一行以 -1 结尾
    graph: list[list[int]] = []
    while True:
        token = int(next(it))
        if token == -1:
            break
        row: list[int] = []
        while token != -2:
            row.append(token)
            token = int(next(it))
        graph.append(row)

    n = len(graph) - 1  # 终点编号为 N
    candidates = range(1, n)

    # 第一问：删除点 v 后，从 0 无法到达 n
    unavoidable = [v for v in candidates if n not in reachable_nodes(graph, 0, blocked=v)]

    # 第二问：在第一问基础上，后半段从 v 出发能到达的点集与前半段（0 到达的点集）仅交于 {v}
    splitting = [
        v
        for v in unavoidable
        if reachable_nodes(graph, 0, blocked=v).isdisjoint(reachable_nodes(graph, v))
    ]

    print(len(unavoidable), *unavoidable)
    print(len(splitting), *splitting)


if __name__ == "__main__":
    solve()
