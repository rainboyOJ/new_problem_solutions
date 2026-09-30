#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys
from collections import deque


def find(fa: list[int], x: int) -> int:
    """并查集查根：路径压缩。"""
    while fa[x] != x:
        fa[x] = fa[fa[x]]
        x = fa[x]
    return x


def kruskal(n: int, edges: list[tuple[int, int, int]]) -> tuple[int, list[list[tuple[int, int]]], list[bool]]:
    """Kruskal 求最小生成树：返回 (总权, 邻接表, 每条边是否在树上)。"""
    fa = list(range(n + 1))
    adj: list[list[tuple[int, int]]] = [[] for _ in range(n + 1)]
    in_tree = [False] * len(edges)
    total = 0
    for i, (x, y, z) in enumerate(sorted(edges, key=lambda e: e[2])):
        rx, ry = find(fa, x), find(fa, y)
        if rx != ry:
            fa[rx] = ry
            total += z
            in_tree[i] = True
            adj[x].append((y, z))
            adj[y].append((x, z))
    return total, adj, in_tree


def max_on_path(adj: list[list[tuple[int, int]]], u: int, target: int) -> int:
    """树上 BFS 找 u 到 target 的路径，返回该路径上的最大边权。"""
    # parent[v] = (前驱节点, 该段边权)，用于回溯整条路径
    parent: dict[int, tuple[int, int]] = {u: (0, 0)}
    q = deque([u])
    while q:
        cur = q.popleft()
        if cur == target:
            break
        for nxt, w in adj[cur]:
            if nxt not in parent:
                parent[nxt] = (cur, w)
                q.append(nxt)
    # 回溯路径上的所有边权取最大
    best = 0
    cur = target
    while cur != u:
        prev, w = parent[cur]
        best = max(best, w)
        cur = prev
    return best


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    edges = [(next(data), next(data), next(data)) for _ in range(m)]

    mst, adj, in_tree = kruskal(n, edges)

    # 枚举每条非树边 (u,v,z)：替换 MST 中 u-v 路径上的最大边得到候选方案。
    # z 等于路径最大边时候选值 = mst（等权替换），题目要严格第二小，只保留 > mst 的候选。
    ans = min(
        mst + z - max_on_path(adj, x, y)
        for i, (x, y, z) in enumerate(edges)
        if not in_tree[i] and z > max_on_path(adj, x, y)
    )
    print(ans)


if __name__ == "__main__":
    solve()
