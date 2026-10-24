#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-24 18:05
# update_at: 2026-10-24 18:05
# P5536 【XR-3】核心城市：剥叶分层，层号最大的 k 个点当核心，答案是第 k+1 大层号。

import sys
from collections import deque


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, k = next(data), next(data)

    graph = [[] for _ in range(n + 1)]  # graph[u]：与城市 u 直接相连的城市
    remain = [0] * (n + 1)              # remain[u]：剥叶过程中 u 还剩几条边
    for _ in range(n - 1):
        u, v = next(data), next(data)
        graph[u].append(v)
        graph[v].append(u)
        remain[u] += 1
        remain[v] += 1

    layer = [0] * (n + 1)               # layer[u]：u 在第几轮被剥掉，叶子是第 1 轮
    queue = deque()
    for node in range(1, n + 1):
        if remain[node] <= 1:           # 叶子的层号是 1
            layer[node] = 1
            queue.append(node)

    # 逐轮往里剥：出队一个已剥掉的点，把邻居的剩余边数减一；减到 1 就是新叶子。
    while queue:
        node = queue.popleft()
        for neighbor in graph[node]:
            if remain[neighbor] <= 1:   # 已剥掉的邻居不再处理
                continue
            remain[neighbor] -= 1
            if remain[neighbor] == 1:
                layer[neighbor] = layer[node] + 1
                queue.append(neighbor)

    # 层号降序的第 k+1 个就是答案（下标 k，因为 layer[0] 是占位）。
    print(sorted(layer[1:], reverse=True)[k])


if __name__ == "__main__":
    solve()
