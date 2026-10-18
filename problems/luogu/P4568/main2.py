#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-18 20:26
# update_at: 2026-10-18 20:26
#
# main2.py：显式建分层图，再在展开后的图上跑一次普通 Dijkstra。
# 与 main.py 的二维 dis 写法等价：这里把「用了几次免费机会」变成点编号的一部分。
# 点数 n(k+1) 最多 1.1e5，边数最多约 2.1e6，Python 版的边表偏重，
# 只用来对照建图结构；正式提交用 main.py 的二维 dis 写法更快更省。

import sys
from heapq import heappop, heappush

type WeightedAdj = list[list[tuple[int, int]]]  # graph[node]：若干 (终点, 花费)

INF = 1 << 60


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m, free_limit = next(data), next(data), next(data)
    start, target = next(data), next(data)

    total = n * (free_limit + 1)           # 分层图总点数 = n * (k + 1)
    graph: WeightedAdj = [[] for _ in range(total)]

    def link(u: int, v: int, cost: int) -> None:
        """加一条有向边 u -> v，花费 cost。"""
        graph[u].append((v, cost))

    for _ in range(m):
        u, v, cost = next(data), next(data), next(data)
        for layer in range(free_limit + 1):
            base = layer * n
            # 同一层内部：正常付费坐一次飞机，双向。
            link(base + u, base + v, cost)
            link(base + v, base + u, cost)
            # 层与层之间：花掉一次免费机会，0 代价降到下一层；单向，免费次数只会变多。
            if layer < free_limit:
                link(base + u, base + n + v, 0)
                link(base + v, base + n + u, 0)

    distance = [INF] * total
    distance[start] = 0                     # 起点在第 0 层，编号就是 start 本身
    heap: list[tuple[int, int]] = [(0, start)]

    while heap:
        current, node = heappop(heap)
        if current != distance[node]:
            continue                        # 堆里的过期条目
        for neighbor, cost in graph[node]:
            candidate = current + cost
            if candidate < distance[neighbor]:
                distance[neighbor] = candidate
                heappush(heap, (candidate, neighbor))

    # 题目要求「最多 k 次」，每一层的终点都可能是答案：只取第 k 层会漏掉少用券的更优解。
    print(min(distance[layer * n + target] for layer in range(free_limit + 1)))


if __name__ == "__main__":
    solve()
