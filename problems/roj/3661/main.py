#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 13:58
# update_at: 2026-10-02 13:58

import sys


def find_cycle(adj: list[list[int]]) -> list[tuple[int, int]]:
    """找基环树中唯一的环：DFS 撞到已访问的非父邻居即闭环，沿 parent 链回溯取整环。"""
    n = len(adj) - 1
    parent = [0] * (n + 1)
    seen = bytearray(n + 1)
    seen[1] = 1
    # 显式栈存 (节点, 下一个要检查的邻接下标)，避免递归深度限制
    stack: list[list[int]] = [[1, 0]]
    while stack:
        u, i = stack[-1]
        if i >= len(adj[u]):
            stack.pop()
            continue
        stack[-1][1] = i + 1
        v = adj[u][i]
        if v == parent[u]:
            continue
        if seen[v]:  # 非父邻居已访问 → u 到 v 的 parent 链加上边 (u,v) 就是那个环
            path = [u]
            x = u
            while x != v:
                x = parent[x]
                path.append(x)
            return list(zip(path, path[1:])) + [(u, v)]  # 环上全部边
        seen[v] = 1
        parent[v] = u
        stack.append([v, 0])
    return []  # 连通图 + m=n 必有环，走不到这里


def tree_walk(adj: list[list[int]], cut: tuple[int, int]) -> list[int]:
    """在删去 cut 边后的树上做字典序最小的 DFS：总是走向编号最小的未访问邻居，
    走投无路时沿原路上退（后退不记录），返回到达城市的记录序列。"""
    n = len(adj) - 1
    skip_u, skip_v = cut  # 被删去的环边两端；(0,0) 表示不删任何边
    vis = bytearray(n + 1)
    vis[1] = 1
    seq = [1]
    path = [0] * (n + 1)   # 显式栈：当前所在的 DFS 路径
    step = [0] * (n + 1)   # 栈中各节点已检查到的邻接表下标
    path[0] = 1
    top = 1
    while top:
        u = path[top - 1]
        adj_u = adj[u]
        i = step[top - 1]
        if i == len(adj_u):  # 邻居全看过了：回退到上一个城市
            top -= 1
            continue
        step[top - 1] = i + 1
        v = adj_u[i]
        if (u == skip_u and v == skip_v) or (u == skip_v and v == skip_u):
            continue  # 环边被删，不能从这里过去
        if vis[v]:
            continue
        vis[v] = 1
        seq.append(v)
        path[top] = v
        step[top] = 0
        top += 1
    return seq


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    adj: list[list[int]] = [[] for _ in range(n + 1)]
    for _ in range(m):
        u, v = next(data), next(data)
        adj[u].append(v)
        adj[v].append(u)
    for adj_u in adj:
        adj_u.sort()  # 邻接表升序：贪心"走最小编号"就是顺序扫描

    # 记录序列 = 某棵生成树的先根序；m=n 时合法生成树 = 删掉环上一条边，逐个试取最小
    cuts = find_cycle(adj) if m == n else [(0, 0)]
    best = tree_walk(adj, cuts[0])
    for cut in cuts[1:]:
        seq = tree_walk(adj, cut)
        if seq < best:
            best = seq

    print(' '.join(map(str, best)))


if __name__ == "__main__":
    solve()
