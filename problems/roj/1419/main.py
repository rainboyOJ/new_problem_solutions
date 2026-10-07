#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 15:12
# update_at: 2026-10-07 15:45

import sys
from collections import deque

INF = 4 * 10**18  # 松弛起点：比最负路径 -(n-1)*1e9 ≈ -2e13 大若干数量级

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Graph = list[list[tuple[int, int]]]  # g[u] = 出边列表，每条边是 (终点 v, 边权 w)


def shortest(n: int, g: Graph) -> int:
    """SPFA：以 1 为源点做队列优化的 Bellman-Ford，回答“1 到 n 的最短距离”。"""
    dist = [INF] * (n + 1)  # dist[u]：1 到 u 的当前最短距离
    inq = bytearray(n + 1)  # inq[u] = 1 表示 u 正在队列里，避免同一时刻重复入队
    dist[1] = 0
    q = deque([1])
    inq[1] = 1
    push_back = q.append
    push_front = q.appendleft
    pop_front = q.popleft
    while q:
        u = pop_front()
        inq[u] = 0
        du = dist[u]
        head_dist = dist[q[0]] if q else INF  # 队首距离，SLF 小优化用
        for v, w in g[u]:
            nd = du + w
            if nd < dist[v]:  # 找到更短的路，v 需要重新入队
                dist[v] = nd
                if not inq[v]:
                    inq[v] = 1
                    if nd < head_dist:  # SLF：估计距离更小的点插到队首优先处理
                        push_front(v)
                        head_dist = nd
                    else:
                        push_back(v)
    return dist[n]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    g: Graph = [[] for _ in range(n + 1)]
    for _ in range(m):
        s, t, d = next(data), next(data), next(data)
        g[s].append((t, d))
    for edges in g:
        edges.reverse()  # 头插建图，出边顺序与 C++ 链式前向星一致
    print(shortest(n, g))


if __name__ == "__main__":
    solve()
