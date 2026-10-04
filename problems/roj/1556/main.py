#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys

LOGN = 16  # 2^15 = 32768 > 10000


def build_lca_table(n: int, adj: list[list[tuple[int, int]]], root: int = 1) -> tuple[list[int], list[int], list[list[int]]]:
    """BFS 遍历树，返回每个节点的深度、到根距离以及倍增祖先表。"""
    depth = [0] * (n + 1)
    dist = [0] * (n + 1)
    up = [[0] * LOGN for _ in range(n + 1)]
    visited = [False] * (n + 1)

    queue = [root]
    visited[root] = True
    head = 0
    while head < len(queue):
        u = queue[head]
        head += 1
        for v, w in adj[u]:
            if not visited[v]:
                visited[v] = True
                depth[v] = depth[u] + 1
                dist[v] = dist[u] + w
                up[v][0] = u
                for k in range(1, LOGN):
                    up[v][k] = up[up[v][k - 1]][k - 1]
                queue.append(v)

    return depth, dist, up


def query_lca(u: int, v: int, depth: list[int], up: list[list[int]]) -> int:
    """求节点 u 和 v 的最近公共祖先 (LCA)。"""
    if depth[u] < depth[v]:
        u, v = v, u

    diff = depth[u] - depth[v]
    for k in range(LOGN):
        if (diff >> k) & 1:
            u = up[u][k]

    if u == v:
        return u

    for k in range(LOGN - 1, -1, -1):
        if up[u][k] != up[v][k]:
            u = up[u][k]
            v = up[v][k]

    return up[u][0]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data, None)
    if n is None:
        return
    m = next(data)

    adj: list[list[tuple[int, int]]] = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        u, v, w = next(data), next(data), next(data)
        adj[u].append((v, w))
        adj[v].append((u, w))

    depth, dist, up = build_lca_table(n, adj, root=1)

    out: list[str] = []
    for _ in range(m):
        u, v = next(data), next(data)
        lca = query_lca(u, v, depth, up)
        ans = dist[u] + dist[v] - 2 * dist[lca]
        out.append(str(ans))

    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == "__main__":
    solve()
