#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 15:55
# update_at: 2026-09-30 15:55

import sys
from collections.abc import Iterator


def find_bridge_components(n: int, edges: list[tuple[int, int]]) -> list[int]:
    """通过 Tarjan 算法求出无向图各顶点所属的边双连通分量 (e-DCC) 编号。"""
    adj: list[list[tuple[int, int]]] = [[] for _ in range(n + 1)]
    for eid, (u, v) in enumerate(edges):
        adj[u].append((v, eid))
        adj[v].append((u, eid))

    dfn = [0] * (n + 1)
    low = [0] * (n + 1)
    dcc = [0] * (n + 1)
    clock = 0
    dcc_cnt = 0
    stack: list[int] = []

    # 显式栈模拟 Tarjan DFS 遍历，避免递归深度受限
    # 栈元素: (当前节点 u, 遍历边生成器/游标, 来向边 id)
    for start in range(1, n + 1):
        if dfn[start]:
            continue
        call_stack: list[tuple[int, Iterator[tuple[int, int]], int]] = []
        clock += 1
        dfn[start] = low[start] = clock
        stack.append(start)
        call_stack.append((start, iter(adj[start]), -1))

        while call_stack:
            u, it, in_eid = call_stack[-1]
            try:
                v, eid = next(it)
                if eid == in_eid:
                    continue
                if not dfn[v]:
                    clock += 1
                    dfn[v] = low[v] = clock
                    stack.append(v)
                    call_stack.append((v, iter(adj[v]), eid))
                else:
                    low[u] = min(low[u], dfn[v])
            except StopIteration:
                call_stack.pop()
                if call_stack:
                    p = call_stack[-1][0]
                    low[p] = min(low[p], low[u])
                if dfn[u] == low[u]:
                    dcc_cnt += 1
                    while True:
                        node = stack.pop()
                        dcc[node] = dcc_cnt
                        if node == u:
                            break

    return dcc


def count_leaf_components(dcc: list[int], edges: list[tuple[int, int]]) -> int:
    """统计边双缩点后度数为 1 的树叶子节点数量。"""
    dcc_cnt = max(dcc) if dcc else 0
    degree = [0] * (dcc_cnt + 1)
    for u, v in edges:
        if dcc[u] != dcc[v]:
            degree[dcc[u]] += 1
            degree[dcc[v]] += 1
    return sum(1 for d in degree[1:] if d == 1)


def solve() -> None:
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    it = iter(input_data)
    n = int(next(it))
    m = int(next(it))
    edges = [(int(next(it)), int(next(it))) for _ in range(m)]

    dcc = find_bridge_components(n, edges)
    leaf_cnt = count_leaf_components(dcc, edges)
    print((leaf_cnt + 1) // 2)


if __name__ == "__main__":
    solve()
