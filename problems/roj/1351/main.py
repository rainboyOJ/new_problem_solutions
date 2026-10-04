#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-08 10:30
# update_at: 2026-07-08 10:30

import sys
from collections import deque


def topological_sort(n: int, children: list[list[int]]) -> list[int]:
    """Kahn 拓扑排序：父节点必须排在所有后代之前。"""
    indeg = [0] * (n + 1)
    for u in range(1, n + 1):
        for v in children[u]:
            indeg[v] += 1

    q = deque(u for u in range(1, n + 1) if indeg[u] == 0)
    order: list[int] = []
    while q:
        u = q.popleft()
        order.append(u)
        for v in children[u]:
            indeg[v] -= 1
            if indeg[v] == 0:
                q.append(v)
    return order


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    children: list[list[int]] = [[] for _ in range(n + 1)]
    for u in range(1, n + 1):
        while (v := next(data)) != 0:
            children[u].append(v)

    print(' '.join(map(str, topological_sort(n, children))))


if __name__ == "__main__":
    solve()
