#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 14:55
# update_at: 2026-09-30 14:55

import sys
from collections import deque

INF = 10**9


def compute_min_prices(n: int, prices: list[int], graph: list[list[int]]) -> list[int]:
    """计算从 1 号城市到达各城市路径上的最小买入价格。"""
    min_p = [INF] * (n + 1)
    min_p[1] = prices[1]
    queue: deque[int] = deque([1])

    while queue:
        u = queue.popleft()
        p = min_p[u]
        for v in graph[u]:
            cand = min(p, prices[v])
            if cand < min_p[v]:
                min_p[v] = cand
                queue.append(v)
    return min_p


def compute_max_prices(n: int, prices: list[int], rev_graph: list[list[int]]) -> list[int]:
    """计算从各城市出发到达 n 号城市路径上的最大卖出价格。"""
    max_p = [-1] * (n + 1)
    max_p[n] = prices[n]
    queue: deque[int] = deque([n])

    while queue:
        u = queue.popleft()
        p = max_p[u]
        for v in rev_graph[u]:
            cand = max(p, prices[v])
            if cand > max_p[v]:
                max_p[v] = cand
                queue.append(v)
    return max_p


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    try:
        n_token = next(data)
    except StopIteration:
        return
    n, m = int(n_token), int(next(data))
    prices = [0] + [int(next(data)) for _ in range(n)]

    graph: list[list[int]] = [[] for _ in range(n + 1)]
    rev_graph: list[list[int]] = [[] for _ in range(n + 1)]

    for _ in range(m):
        u, v, t = int(next(data)), int(next(data)), int(next(data))
        graph[u].append(v)
        rev_graph[v].append(u)
        if t == 2:
            graph[v].append(u)
            rev_graph[u].append(v)

    min_p = compute_min_prices(n, prices, graph)
    max_p = compute_max_prices(n, prices, rev_graph)

    best_profit = max((max_p[i] - min_p[i] for i in range(1, n + 1) if min_p[i] <= 100 and max_p[i] >= 0), default=0)
    print(best_profit)


if __name__ == "__main__":
    solve()
