#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 06:00
# update_at: 2026-10-01 06:00

import sys
from collections import deque

INF = 1 << 60
level: list[int] = []  # 层次图：每个点在残量网络上的层次，-1 = 未访问
it: list[int] = []     # 当前弧：每个点下一次要尝试的邻接点下标


def bfs(cap: list[list[int]], s: int, t: int) -> bool:
    """在残量网络上从 s 分层，返回汇点 t 是否仍可达（还有增广路）。"""
    global level
    level = [-1] * len(cap)
    level[s] = 0
    queue = deque([s])
    while queue:
        u = queue.popleft()
        for v, c in enumerate(cap[u]):
            if c and level[v] < 0:  # 该排水沟还有残量且对端没分过层
                level[v] = level[u] + 1
                queue.append(v)
    return level[t] >= 0


def dfs(cap: list[list[int]], u: int, t: int, f: int) -> int:
    """沿层次图从 u 向 t 推一条不超过 f 的流，返回实际推送量。"""
    if u == t:
        return f
    while it[u] < len(cap):
        v = it[u]
        advance = cap[u][v] > 0 and level[v] == level[u] + 1  # 只走层次+1 的残量边
        if advance:
            pushed = dfs(cap, v, t, min(f, cap[u][v]))
            if pushed:
                cap[u][v] -= pushed  # 正向边扣残量，反向边留出可回退的容量
                cap[v][u] += pushed
                return pushed
        it[u] += 1  # 这条边再也推不动，当前弧后移
    return 0


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    # 邻接矩阵存容量：平行边直接累加；起点=终点的自环不贡献流量
    cap = [[0] * m for _ in range(m)]
    for _ in range(n):
        s, e, c = next(data), next(data), next(data)
        if s != e:
            cap[s - 1][e - 1] += c

    flow = 0
    while bfs(cap, 0, m - 1):  # 水潭 0 → 小溪 m-1
        global it
        it = [0] * m
        while pushed := dfs(cap, 0, m - 1, INF):
            flow += pushed
    print(flow)


if __name__ == "__main__":
    solve()
