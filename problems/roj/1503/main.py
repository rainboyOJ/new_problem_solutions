#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 15:06
# update_at: 2026-09-30 15:06

import sys
from heapq import heappop, heappush
from collections import deque

INF = 1 << 60  # 不可达哨兵，远大于任何真实最短路（≤ T·10^4）


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    T, R, P = next(data), next(data), next(data)
    S = next(data)

    # roads：双向非负权边；planes：单向可负权边
    roads: list[list[tuple[int, int]]] = [[] for _ in range(T + 1)]
    planes: list[list[tuple[int, int]]] = [[] for _ in range(T + 1)]
    for _ in range(R):
        a, b, c = next(data), next(data), next(data)
        roads[a].append((b, c))
        roads[b].append((a, c))
    for _ in range(P):
        a, b, c = next(data), next(data), next(data)
        planes[a].append((b, c))

    # 第一步：道路双向，所在连通块内部能自由走动 —— 缩成一个点
    comp = [-1] * (T + 1)
    members: list[list[int]] = []  # 每个块的成员，用于给块内 Dijkstra 建多源堆
    for s in range(1, T + 1):
        if comp[s] != -1:
            continue
        comp[s] = len(members)
        block = [s]
        q = deque([s])
        while q:
            u = q.popleft()
            for v, _ in roads[u]:
                if comp[v] == -1:
                    comp[v] = len(members)
                    block.append(v)
                    q.append(v)
        members.append(block)

    # 第二步：航线必然跨块（块内航线会违反题面保证），缩点后构成 DAG，用入度定拓扑序
    dag: list[list[int]] = [[] for _ in members]
    indeg = [0] * len(members)
    for a in range(1, T + 1):
        for b, _ in planes[a]:
            dag[comp[a]].append(comp[b])
            indeg[comp[b]] += 1

    # 第三步：按拓扑序逐块 Dijkstra。处理块 c 时，所有指向它的跨块航线起点
    # 都已定值，块内每个点的答案也就此确定，负权不会破坏 Dijkstra 的前提。
    dist = [INF] * (T + 1)
    dist[S] = 0
    topo = deque(c for c in range(len(members)) if indeg[c] == 0)
    while topo:
        c = topo.popleft()
        heap = sorted((dist[u], u) for u in members[c] if dist[u] < INF)
        while heap:
            d, u = heappop(heap)
            if d > dist[u]:
                continue
            for v, w in planes[u]:  # 跨块航线：只是给别的块送初值，不入本块的堆
                if d + w < dist[v]:
                    dist[v] = d + w
            for v, w in roads[u]:  # 道路权非负，Dijkstra 安全
                if d + w < dist[v]:
                    dist[v] = d + w
                    heappush(heap, (dist[v], v))
        for y in dag[c]:
            indeg[y] -= 1
            if indeg[y] == 0:
                topo.append(y)

    sys.stdout.write('\n'.join('NO PATH' if dist[i] == INF else str(dist[i]) for i in range(1, T + 1)))


if __name__ == "__main__":
    solve()
