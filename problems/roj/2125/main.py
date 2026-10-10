#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 07:39
# update_at: 2026-10-08 07:39

import sys
from collections import deque
from collections.abc import Iterator

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Graph = list[list[int]]  # g[u] = u 引用的文章编号，已按编号升序排好


def read_graph(n: int, m: int, data: Iterator[int]) -> Graph:
    """读入 m 条有向边，返回出边升序排序后的邻接表（下标 1..n 对应文章编号）。"""
    g: Graph = [[] for _ in range(n + 1)]
    for _ in range(m):
        x, y = next(data), next(data)
        g[x].append(y)
    for edges in g:
        edges.sort()  # 题面要求：能看的文章多时先看编号小的
    return g


def dfs_order(g: Graph) -> list[int]:
    """从 1 号文章出发的先序 DFS 序列；显式栈代替递归，避免长链爆栈。"""
    order = [1]
    seen = [False] * len(g)
    seen[1] = True
    stack = [(1, 0)]  # (结点, 下一个待扩展的出边下标)，栈顶就是当前递归层
    while stack:
        u, idx = stack[-1]
        if idx < len(g[u]):
            stack[-1] = (u, idx + 1)
            v = g[u][idx]
            if not seen[v]:  # 未看过才深入，看过就换下一条出边
                seen[v] = True
                order.append(v)
                stack.append((v, 0))
        else:
            stack.pop()  # 出边走完，回溯
    return order


def bfs_order(g: Graph) -> list[int]:
    """从 1 号文章出发的 BFS 序列；出队时按升序展开出边，入队即判重。"""
    order = [1]
    seen = [False] * len(g)
    seen[1] = True
    q = deque([1])
    while q:
        u = q.popleft()  # 队首文章，按升序展开它的参考文献
        for v in g[u]:
            if not seen[v]:
                seen[v] = True
                order.append(v)
                q.append(v)
    return order


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)  # 文章数、引用关系数
    g = read_graph(n, m, data)
    # 两行答案：先 DFS 序列，再 BFS 序列
    out = (" ".join(map(str, dfs_order(g))), " ".join(map(str, bfs_order(g))))
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
