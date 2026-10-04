#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 15:44
# update_at: 2026-09-30 15:44

import sys


def post_order(graph: list[list[int]]) -> list[int]:
    """Kosaraju 第一遍：迭代 DFS 全图，按离开时间（后序）记录每个点。"""
    n = len(graph)
    seen = [False] * n
    order: list[int] = []
    for start in range(n):
        if seen[start]:
            continue
        seen[start] = True
        stack = [(start, 0)]  # (点, 下一条待访问的边下标)
        while stack:
            u, i = stack[-1]
            if i < len(graph[u]):          # 还有邻居没看过：压入下一个邻居
                stack[-1] = (u, i + 1)
                v = graph[u][i]
                if not seen[v]:
                    seen[v] = True
                    stack.append((v, 0))
            else:                          # 邻居耗尽：后序出栈
                stack.pop()
                order.append(u)
    return order


def assign_components(rg: list[list[int]], order: list[int]) -> list[int]:
    """Kosaraju 第二遍：按离开时间倒序在反图上 DFS，每棵 DFS 树缩成一个强连通分量，返回每个点的分量编号。"""
    comp = [-1] * len(rg)
    comp_id = 0
    for start in reversed(order):
        if comp[start] != -1:
            continue
        comp[start] = comp_id
        stack = [start]
        while stack:
            u = stack.pop()
            for v in rg[u]:
                if comp[v] == -1:
                    comp[v] = comp_id
                    stack.append(v)
        comp_id += 1
    return comp


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    it = iter(data)
    n = next(it)

    # 邻接表 + 逆邻接表：矩阵按行读，g[i] 存 i 能直接传到的点，rg 存反向边
    g: list[list[int]] = [[] for _ in range(n)]
    rg: list[list[int]] = [[] for _ in range(n)]
    for u in range(n):
        for v in range(n):
            if next(it):  # C[u][v] == 1 表示 u 能直接传给 v
                g[u].append(v)
                rg[v].append(u)

    # 缩点成 DAG：入度为 0 的强连通分量必须各传一个起始奸细
    comp = assign_components(rg, post_order(g))
    has_in = [False] * (max(comp) + 1 if n else 0)
    for u in range(n):
        cu = comp[u]
        for v in g[u]:
            if comp[v] != cu:  # 跨分量边给目标分量记一次入度
                has_in[comp[v]] = True

    print(has_in.count(False))


if __name__ == "__main__":
    solve()
