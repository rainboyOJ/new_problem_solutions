#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-05-22 19:17
# update_at: 2026-05-22 19:17

import sys

INF = 10**18


def combine(max1: int, max2: int, cand1: int, cand2: int) -> tuple[int, int]:
    """合并两条路径段的最大权与严格次大权。"""
    cands = {max1, max2, cand1, cand2} - {-1}
    m1 = max(cands) if cands else -1
    cands.discard(m1)
    m2 = max(cands) if cands else -1
    return m1, m2


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    m = next(data)

    # 读入所有边并按边权升序排序
    edges: list[tuple[int, int, int]] = []
    for _ in range(m):
        u = next(data)
        v = next(data)
        w = next(data)
        edges.append((w, u, v))
    edges.sort()

    # Kruskal 算法求最小生成树
    parent = list(range(n + 1))

    def find(i: int) -> int:
        path: list[int] = []
        while parent[i] != i:
            path.append(i)
            i = parent[i]
        for node in path:
            parent[node] = i
        return i

    mst_adj: list[list[tuple[int, int]]] = [[] for _ in range(n + 1)]
    non_mst_edges: list[tuple[int, int, int]] = []
    mst_weight = 0
    edges_count = 0

    for w, u, v in edges:
        root_u, root_v = find(u), find(v)
        if root_u != root_v:
            parent[root_u] = root_v
            mst_adj[u].append((v, w))
            mst_adj[v].append((u, w))
            mst_weight += w
            edges_count += 1
        else:
            non_mst_edges.append((w, u, v))

    # BFS 建立倍增表
    LOGN = 18
    up = [[0] * (n + 1) for _ in range(LOGN)]
    f1 = [[-1] * (n + 1) for _ in range(LOGN)]
    f2 = [[-1] * (n + 1) for _ in range(LOGN)]
    depth = [0] * (n + 1)

    # 从节点 1 开始 BFS
    queue = [1]
    depth[1] = 1
    head = 0
    while head < len(queue):
        u = queue[head]
        head += 1
        for v, w in mst_adj[u]:
            if not depth[v]:
                depth[v] = depth[u] + 1
                up[0][v] = u
                f1[0][v] = w
                queue.append(v)

    # 预处理 2^k 级祖先与路径上的最大/次大边权
    for k in range(LOGN - 1):
        up_k = up[k]
        up_next = up[k + 1]
        f1_k, f2_k = f1[k], f2[k]
        f1_next, f2_next = f1[k + 1], f2[k + 1]
        for v in range(1, n + 1):
            p = up_k[v]
            up_next[v] = up_k[p]
            f1_next[v], f2_next[v] = combine(f1_k[v], f2_k[v], f1_k[p], f2_k[p])

    def query_max(u: int, v: int) -> tuple[int, int]:
        """查询树上 u 到 v 路径上的最大边权与严格次大边权。"""
        m1, m2 = -1, -1
        if depth[u] < depth[v]:
            u, v = v, u

        # 提升 u 使 depth[u] == depth[v]
        diff = depth[u] - depth[v]
        for k in range(LOGN):
            if (diff >> k) & 1:
                m1, m2 = combine(m1, m2, f1[k][u], f2[k][u])
                u = up[k][u]

        if u == v:
            return m1, m2

        for k in range(LOGN - 1, -1, -1):
            if up[k][u] != up[k][v]:
                m1, m2 = combine(m1, m2, f1[k][u], f2[k][u])
                m1, m2 = combine(m1, m2, f1[k][v], f2[k][v])
                u = up[k][u]
                v = up[k][v]

        m1, m2 = combine(m1, m2, f1[0][u], f2[0][u])
        m1, m2 = combine(m1, m2, f1[0][v], f2[0][v])
        return m1, m2

    min_delta = INF
    for w, u, v in non_mst_edges:
        m1, m2 = query_max(u, v)
        if w > m1:
            diff = w - m1
            if diff < min_delta:
                min_delta = diff
        elif w > m2 and m2 != -1:
            diff = w - m2
            if diff < min_delta:
                min_delta = diff

    print(mst_weight + min_delta)


if __name__ == "__main__":
    solve()
