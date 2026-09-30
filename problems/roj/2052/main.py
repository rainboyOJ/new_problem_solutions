#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 05:24
# update_at: 2026-10-01 05:24

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    fence_cnt = next(data)

    # 邻接表存 (邻居, 边号)，按邻居升序排：走最小顶点 = 字典序最小的前提
    adj: list[list[tuple[int, int]]] = [[] for _ in range(501)]
    for eid in range(fence_cnt):
        a, b = next(data), next(data)
        adj[a].append((b, eid))
        adj[b].append((a, eid))
    for fences in adj:
        fences.sort()

    # 欧拉路径必须从奇点出发；全偶时起点可任选，取最小顶点让字典序最小
    odd_vertices = [v for v in range(501) if len(adj[v]) & 1]
    start = odd_vertices[0] if odd_vertices else next(v for v in range(501) if adj[v])

    used = [False] * fence_cnt
    scan = [0] * 501   # 每个顶点在邻接表上的扫描位置，只前进不后退
    stack = [start]
    path: list[int] = []   # 逆后序：顶点所有边用完才出栈

    while stack:
        v = stack[-1]
        while scan[v] < len(adj[v]) and used[adj[v][scan[v]][1]]:
            scan[v] += 1                     # 跳过已走过的边，每个位置最多扫一次
        if scan[v] == len(adj[v]):           # 没有剩余边 → 完成该顶点
            path.append(stack.pop())
        else:
            u, eid = adj[v][scan[v]]         # 最小邻居优先
            used[eid] = True
            stack.append(u)

    # 逆后序反转即为从 start 出发的路径
    print('\n'.join(map(str, reversed(path))))


if __name__ == "__main__":
    solve()
