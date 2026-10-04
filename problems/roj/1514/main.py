#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-05-22 19:17
# update_at: 2026-05-22 19:17

import sys


def tarjan_scc(n: int, adj: list[list[int]]) -> tuple[int, list[int], list[int]]:
    """用 Tarjan 算法缩点，返回 (scc 数量, 每个原点的 scc 编号, 每个 scc 的点权/大小)。

    由于递归在 N=10^5 时深度极大，使用非递归显式栈模拟 DFS。
    """
    dfn = [0] * (n + 1)
    low = [0] * (n + 1)
    scc = [0] * (n + 1)
    in_stk = [False] * (n + 1)
    stk: list[int] = []
    timer = 0
    scc_cnt = 0
    scc_size = [0]  # 下标 1-based

    # 显式栈模拟 Tarjan DFS: (u, edge_index)
    for root in range(1, n + 1):
        if dfn[root]:
            continue
        call_stk = [(root, 0)]
        timer += 1
        dfn[root] = low[root] = timer
        stk.append(root)
        in_stk[root] = True

        while call_stk:
            u, i = call_stk[-1]
            if i < len(adj[u]):
                call_stk[-1] = (u, i + 1)
                v = adj[u][i]
                if not dfn[v]:
                    timer += 1
                    dfn[v] = low[v] = timer
                    stk.append(v)
                    in_stk[v] = True
                    call_stk.append((v, 0))
                elif in_stk[v] and dfn[v] < low[u]:
                    low[u] = dfn[v]
            else:
                call_stk.pop()
                if call_stk:
                    p = call_stk[-1][0]
                    if low[u] < low[p]:
                        low[p] = low[u]
                if dfn[u] == low[u]:
                    scc_cnt += 1
                    sz = 0
                    while True:
                        node = stk.pop()
                        in_stk[node] = False
                        scc[node] = scc_cnt
                        sz += 1
                        if node == u:
                            break
                    scc_size.append(sz)

    return scc_cnt, scc, scc_size


def build_dag(
    n: int, scc_cnt: int, scc: list[int], edges: list[tuple[int, int]]
) -> tuple[list[list[int]], list[int]]:
    """在强连通分量间建立无重边 DAG，并统计每个新点的入度。"""
    # 边去重：先映射为 (scc[u], scc[v])，去除自环和重边
    scc_edges = sorted(
        (scc[u], scc[v]) for u, v in edges if scc[u] != scc[v]
    )
    dag: list[list[int]] = [[] for _ in range(scc_cnt + 1)]
    in_deg = [0] * (scc_cnt + 1)

    prev_edge = (0, 0)
    for edge in scc_edges:
        if edge != prev_edge:
            u, v = edge
            dag[u].append(v)
            in_deg[v] += 1
            prev_edge = edge

    return dag, in_deg


def find_longest_chain(
    scc_cnt: int, dag: list[list[int]], in_deg: list[int], scc_size: list[int], mod: int
) -> tuple[int, int]:
    """在 DAG 上拓扑排序求最长链的点权和以及方案数。"""
    # 拓扑排序队列：初始入度为 0 的节点
    queue = [u for u in range(1, scc_cnt + 1) if in_deg[u] == 0]
    dp_len = [0] * (scc_cnt + 1)
    dp_cnt = [0] * (scc_cnt + 1)

    for u in queue:
        dp_len[u] = scc_size[u]
        dp_cnt[u] = 1

    head = 0
    while head < len(queue):
        u = queue[head]
        head += 1
        for v in dag[u]:
            cand_len = dp_len[u] + scc_size[v]
            if cand_len > dp_len[v]:
                dp_len[v] = cand_len
                dp_cnt[v] = dp_cnt[u]
            elif cand_len == dp_len[v]:
                dp_cnt[v] = (dp_cnt[v] + dp_cnt[u]) % mod

            in_deg[v] -= 1
            if in_deg[v] == 0:
                queue.append(v)

    max_len = max(dp_len)
    total_cnt = sum(
        dp_cnt[u] for u in range(1, scc_cnt + 1) if dp_len[u] == max_len
    ) % mod
    return max_len, total_cnt


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    it = iter(data)
    n = int(next(it))
    m = int(next(it))
    mod = int(next(it))

    edges: list[tuple[int, int]] = []
    adj: list[list[int]] = [[] for _ in range(n + 1)]
    for _ in range(m):
        u = int(next(it))
        v = int(next(it))
        edges.append((u, v))
        adj[u].append(v)

    scc_cnt, scc, scc_size = tarjan_scc(n, adj)
    dag, in_deg = build_dag(n, scc_cnt, scc, edges)
    max_len, total_cnt = find_longest_chain(scc_cnt, dag, in_deg, scc_size, mod)

    print(max_len)
    print(total_cnt)


if __name__ == "__main__":
    solve()
