#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 10:29
# update_at: 2026-10-02 10:29

import sys
from collections import deque

LOG = 14   # 2^14 > 10^4，倍增层数足够覆盖任意树深
INF = 1 << 30


def find(fa: list[int], x: int) -> int:
    """并查集找代表元，隔代路径压缩。"""
    while fa[x] != x:
        fa[x] = fa[fa[x]]
        x = fa[x]
    return x


def kruskal(n: int, edges: list[tuple[int, int, int]]) -> tuple[list[list[tuple[int, int]]], list[int]]:
    """按限重从大到小做最大生成树：返回带权邻接表与最终并查集。

    货车想运得越重越好，所以走"瓶颈最大"的路径——它一定在最大生成树上。
    """
    fa = list(range(n + 1))
    tree: list[list[tuple[int, int]]] = [[] for _ in range(n + 1)]
    for x, y, z in sorted(edges, key=lambda e: e[2], reverse=True):  # 按限重 z 从大到小
        rx, ry = find(fa, x), find(fa, y)
        if rx != ry:
            fa[rx] = ry
            tree[x].append((y, z))
            tree[y].append((x, z))
    return tree, fa


def bfs_root(root: int, tree: list[list[tuple[int, int]]], parent: list[int],
             up_w: list[int], depth: list[int], seen: list[bool]) -> None:
    """从 root 出发 BFS，确定每个点的父亲、到父亲的边权和深度。"""
    seen[root] = True
    dq = deque([root])
    while dq:
        u = dq.popleft()
        for v, w in tree[u]:
            if not seen[v]:
                seen[v] = True
                parent[v] = u
                up_w[v] = w
                depth[v] = depth[u] + 1
                dq.append(v)


def build_tables(n: int, tree: list[list[tuple[int, int]]]) -> tuple[list[list[int]], list[list[int]], list[int]]:
    """建倍增表：up[k][v] 是 v 往上 2^k 级祖先，mn[k][v] 是这段路上最小的限重。"""
    parent = [0] * (n + 1)
    up_w = [0] * (n + 1)   # 每个点到父亲的边权
    depth = [0] * (n + 1)
    seen = [False] * (n + 1)
    for root in range(1, n + 1):          # 生成树可能是森林，每个连通块都要 BFS
        if not seen[root]:
            bfs_root(root, tree, parent, up_w, depth, seen)

    up = [parent[:]]                      # 第 0 层就是父亲数组
    mn = [up_w[:]]
    for _ in range(1, LOG):
        prev_up, prev_mn = up[-1], mn[-1]
        up.append([prev_up[prev_up[v]] for v in range(n + 1)])
        mn.append([min(prev_mn[v], prev_mn[prev_up[v]]) for v in range(n + 1)])
    return up, mn, depth


def query(x: int, y: int, up: list[list[int]], mn: list[list[int]],
          depth: list[int], fa: list[int]) -> int:
    """x 到 y 在最大生成树上的路径最小限重；不在同一连通块返回 -1。"""
    if find(fa, x) != find(fa, y):
        return -1
    if depth[x] < depth[y]:
        x, y = y, x
    ans = INF
    # 先把较深的一方按二进制拆分提升到与另一方同深度，沿途取最小边权
    diff = depth[x] - depth[y]
    for k in range(LOG):
        if diff >> k & 1:
            ans = min(ans, mn[k][x])
            x = up[k][x]
    if x == y:
        return ans
    # 两人一起从高处往下试：2^k 级祖先不同就跳上去，最后在 LCA 的下一层停下
    for k in range(LOG - 1, -1, -1):
        if up[k][x] != up[k][y]:
            ans = min(ans, mn[k][x], mn[k][y])
            x, y = up[k][x], up[k][y]
    return min(ans, mn[0][x], mn[0][y])


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    edges = [(next(data), next(data), next(data)) for _ in range(m)]  # (x, y, z)
    q = next(data)
    queries = [(next(data), next(data)) for _ in range(q)]

    tree, fa = kruskal(n, edges)
    up, mn, depth = build_tables(n, tree)

    print('\n'.join(str(query(x, y, up, mn, depth, fa)) for x, y in queries))


if __name__ == "__main__":
    solve()
