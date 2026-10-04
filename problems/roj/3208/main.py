#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 01:57
# update_at: 2026-10-02 02:05

import sys
from heapq import heappop, heappush

INF = 10**18                    # 最短路里的"不可达"
STEP = ((0, 1), (1, 0))         # 每一步只能往右或往下
TAKE = 1                        # 拿分那条弧的容量：同一个格子只算一次
FREE = 0                        # 借道那条弧的费用：格子被重复经过不再加分


def dag_potential(graph: list[list[int]], to: list[int], cap: list[int],
                  cost: list[int], s: int) -> list[int]:
    """源点到各点的最短路当初始势：拆点编号 0..2N²-1 本身就是 DAG 的拓扑序。"""
    h = [INF] * len(graph)
    h[s] = 0
    for u in range(len(graph)):
        if h[u] == INF:                                         # 尚未连通，跳过
            continue
        for e in graph[u]:
            if cap[e] and h[u] + cost[e] < h[to[e]]:            # 只要还有残量的正向弧
                h[to[e]] = h[u] + cost[e]
    return h


def min_cost_flow(graph: list[list[int]], to: list[int], cap: list[int],
                  cost: list[int], s: int, t: int, need: int) -> int:
    """从 s 往 t 送 need 次单位流，返回最小费用；反向边编号是 e ^ 1。"""
    size = len(graph)
    h = dag_potential(graph, to, cap, cost, s)                  # 有负费用弧，必须先用它定势
    total = 0
    for _ in range(need):
        dist = [INF] * size
        prev = [-1] * size
        dist[s] = 0
        pq = [(0, s)]
        while pq:
            d, u = heappop(pq)
            if d > dist[u]:
                continue
            for e in graph[u]:
                v = to[e]
                if cap[e]:                                      # 只在残量弧上松弛
                    nd = d + cost[e] + h[u] - h[v]              # 约化费用，势成立时非负
                    if nd < dist[v]:
                        dist[v] = nd
                        prev[v] = e
                        heappush(pq, (nd, v))
        if prev[t] < 0:                                         # 送不动了（本题网格总能送满 need 次）
            break
        for v in range(size):
            h[v] += dist[v] if dist[v] < INF else 0
        path: list[int] = []                                    # 这条最短路经过的弧，反向走回去
        v = t
        while v != s:
            path.append(prev[v])
            v = to[prev[v] ^ 1]
        for e in path:
            cap[e] -= 1
            cap[e ^ 1] += 1
        total += sum(cost[e] for e in path)
    return total


def max_gain(grid: list[list[int]], k: int) -> int:
    """k 条从左上到右下的单调路径最多能取走多少整数（同一格只计一次）。"""
    n = len(grid)
    size = 2 * n * n                                            # 格子 i 拆成 入点 2i 与 出点 2i+1
    graph: list[list[int]] = [[] for _ in range(size)]
    to: list[int] = []
    cap: list[int] = []
    cost: list[int] = []

    def link(u: int, v: int, c: int, w: int) -> None:
        """连一条 u->v 容量 c 费用 w 的弧，紧跟一条残量 0、费用相反的弧。"""
        graph[u].append(len(to))
        to.append(v)
        cap.append(c)
        cost.append(w)
        graph[v].append(len(to))
        to.append(u)
        cap.append(0)
        cost.append(-w)

    for i in range(n):
        for j in range(n):
            u = 2 * (i * n + j)
            if grid[i][j]:                                      # 第一条穿过它的路径拿走格子里的数
                link(u, u + 1, TAKE, -grid[i][j])
            link(u, u + 1, k, FREE)                             # 之后的路径只借道，不再加分
            for di, dj in STEP:
                if i + di < n and j + dj < n:
                    link(u + 1, 2 * ((i + di) * n + j + dj), k, FREE)   # 走到右 / 下邻居的入点

    return -min_cost_flow(graph, to, cap, cost, 0, size - 1, k)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, k = next(data), next(data)
    grid = [[next(data) for _ in range(n)] for _ in range(n)]
    print(0 if k == 0 else max_gain(grid, k))


if __name__ == "__main__":
    solve()
