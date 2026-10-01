#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys
from collections import deque


def farthest(adj: list[list[tuple[int, int]]], src: int) -> tuple[int, list[int]]:
    """返回树中离 src 最远的结点编号，以及各结点到 src 的距离（树上路径唯一，BFS 即最短路）。"""
    dist = [-1] * len(adj)
    dist[src] = 0
    dq = deque([src])
    while dq:
        u = dq.popleft()
        for v, w in adj[u]:
            if dist[v] < 0:
                dist[v] = dist[u] + w
                dq.append(v)
    far = max(range(1, len(adj)), key=dist.__getitem__)
    return far, dist


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, s = next(data), next(data)

    adj: list[list[tuple[int, int]]] = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        a, b, w = next(data), next(data), next(data)
        adj[a].append((b, w))
        adj[b].append((a, w))

    # 两次 BFS 定位直径：树上离任一点最远的点必是某条直径的端点
    u0, _ = farthest(adj, 1)
    uk, dist0 = farthest(adj, u0)
    _, distK = farthest(adj, uk)
    diameter = dist0[uk]

    # 满足 d(u0,x)+d(x,uk)=diameter 的 x 恰是直径上的结点，按位置排序
    path = sorted((x for x in range(1, n + 1) if dist0[x] + distK[x] == diameter), key=dist0.__getitem__)
    pos = [dist0[x] for x in path]  # pos[t]：直径第 t 个结点在直径上的位置
    k = len(path)

    # n ≤ 300，直接对每个结点做一次 BFS 得全源距离
    dist_all = [farthest(adj, v)[1] for v in range(1, n + 1)]

    # depAt[t]：以 path[t] 为"挂点"（到直径路径最近的直径结点）的结点的最大距离
    # 结点 v 的路径与直径交于唯一点，argmin 唯一给出挂点，最小值即挂接深度
    depAt = [0] * k
    for v in range(1, n + 1):
        near = min(range(k), key=lambda t: dist_all[v - 1][path[t]])
        depAt[near] = max(depAt[near], dist_all[v - 1][path[near]])

    # 枚举直径上的候选核 [i..j]（长度 ≤ s），双指针保证 j 只增不减
    # 窗口外两侧结点的距离被 pos[i]、diameter-pos[j] 支配（可证 挂深 ≤ 挂点到较远端点的长）
    ans = diameter
    j = 0
    for i in range(k):
        if j < i:
            j = i
        while j + 1 < k and pos[j + 1] - pos[i] <= s:
            j += 1
        cover = max(depAt[i : j + 1])  # 窗口内挂点深度
        left_tail = pos[i]             # 直径左端到核左端的距离
        right_tail = diameter - pos[j]  # 直径右端到核右端的距离
        ans = min(ans, max(cover, left_tail, right_tail))

    print(ans)


if __name__ == "__main__":
    solve()
