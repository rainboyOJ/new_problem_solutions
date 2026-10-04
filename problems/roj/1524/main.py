#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 16:06
# update_at: 2026-09-30 16:06

import sys
from collections.abc import Iterator

# 题目数据可能包含多达 30000 个节点，链状图递归会导致深度过大
sys.setrecursionlimit(100000)


def count_bridges(n: int, adj: list[list[tuple[int, int]]]) -> int:
    """计算无向图中割边（桥）的数量。

    使用 Tarjan 算法求割边：当 low[v] > dfn[u] 时，树边 (u, v) 为割边。
    每个邻接点附带边的唯一编号 edge_id，防止沿反向边直接走回父节点。
    图可能不连通，需要遍历所有未访问节点。
    """
    dfn = [0] * (n + 1)
    low = [0] * (n + 1)
    timer = 0
    bridges = 0

    # 用迭代 DFS 彻底避免递归爆栈与函数调用开销
    for start in range(1, n + 1):
        if dfn[start]:
            continue
        timer += 1
        dfn[start] = low[start] = timer
        # 栈元素: (当前节点 u, 入边编号 in_edge, 正在遍历的邻接表索引 edge_idx)
        stack = [(start, -1, 0)]

        while stack:
            u, in_edge, idx = stack[-1]
            if idx < len(adj[u]):
                v, eid = adj[u][idx]
                stack[-1] = (u, in_edge, idx + 1)
                if eid == in_edge:
                    continue  # 跳过同一条无向边的反向边
                if dfn[v]:
                    low[u] = min(low[u], dfn[v])
                else:
                    timer += 1
                    dfn[v] = low[v] = timer
                    stack.append((v, eid, 0))
            else:
                stack.pop()
                if stack:
                    p = stack[-1][0]
                    low[p] = min(low[p], low[u])
                    if low[u] > dfn[p]:
                        bridges += 1

    return bridges


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []

    while True:
        try:
            m = next(data)
            n = next(data)
        except StopIteration:
            break
        if m == 0 and n == 0:
            break

        adj: list[list[tuple[int, int]]] = [[] for _ in range(m + 1)]
        for eid in range(n):
            u, v = next(data), next(data)
            adj[u].append((v, eid))
            adj[v].append((u, eid))

        bridges = count_bridges(m, adj)
        out.append(str(bridges))

    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == "__main__":
    solve()
