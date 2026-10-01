#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 07:46
# update_at: 2026-10-01 07:46

import sys


def component_ids(adj: list[list[int]], rev: list[list[int]]) -> list[int]:
    """Kosaraju：返回每个学校所属强连通分量的编号（编号连续，从 0 开始）。

    第一遍在反图上求逆后序，第二遍按逆后序在原图上扩散染色。
    两遍都用手写栈代替递归，避免 N 较大时压爆解释器栈。
    """
    n = len(adj)
    order: list[int] = []
    seen = bytearray(n)
    for s in range(n):
        if seen[s]:
            continue
        stack: list[int] = [s]
        while stack:
            v = stack.pop()
            if v < 0:                       # ~v 是“离开 v”的标记，此刻 v 的后代都已离开
                order.append(~v)
                continue
            if seen[v]:                     # 同一个点可能被压入多次，只在第一次弹出时展开
                continue
            seen[v] = 1                     # 展开的这一刻就标记，离开标记一定排在孩子下面
            stack.append(~v)
            for w in rev[v]:
                if not seen[w]:
                    stack.append(w)

    comp = [-1] * n
    cid = 0
    for v in reversed(order):
        if comp[v] != -1:
            continue
        comp[v] = cid
        stack = [v]
        while stack:
            u = stack.pop()
            for w in adj[u]:
                if comp[w] == -1:
                    comp[w] = cid
                    stack.append(w)
        cid += 1
    return comp


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    adj: list[list[int]] = []
    for _ in range(n):
        row: list[int] = []
        while (x := next(data)) != 0:       # 每行列出接受学校，0 表示列表结束
            row.append(x - 1)
        adj.append(row)

    rev: list[list[int]] = [[] for _ in range(n)]
    for v, row in enumerate(adj):
        for w in row:
            rev[w].append(v)                # 反向边：Kosaraju 第一遍要跑在反图上

    comp = component_ids(adj, rev)
    total = max(comp) + 1                   # 分量编号恰好占满 0..total-1

    # 软件在同一分量内可以互相送达，缩点后只需数出“源分量”和“汇分量”的个数。
    has_in = bytearray(total)               # 有跨分量入边的分量，不可能是源
    has_out = bytearray(total)              # 有跨分量出边的分量，不可能是汇
    for v, row in enumerate(adj):
        for w in row:
            a, b = comp[v], comp[w]
            if a != b:
                has_out[a] = 1
                has_in[b] = 1
    sources = total - sum(has_in)
    sinks = total - sum(has_out)

    print(sources)                                          # 子任务 A
    print(0 if total == 1 else max(sources, sinks))         # 子任务 B


if __name__ == "__main__":
    solve()
