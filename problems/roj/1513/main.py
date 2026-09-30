#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 15:35
# update_at: 2026-09-30 15:35

import sys


def postorder(n: int, g: list[list[int]]) -> list[int]:
    """原图上迭代 DFS 的后序序列：Kosaraju 第一遍，后走完的点先被第二遍处理。"""
    seen = [False] * n
    order: list[int] = []
    for start in range(n):
        if seen[start]:
            continue
        seen[start] = True
        stack = [(start, 0)]  # (点, 已走到第几条出边)
        while stack:
            v, i = stack.pop()
            if i < len(g[v]):
                stack.append((v, i + 1))   # 回溯后从下一条出边继续
                w = g[v][i]
                if not seen[w]:
                    seen[w] = True
                    stack.append((w, 0))
            else:
                order.append(v)            # 所有出边走完才入序，即后序
    return order


def assign_components(n: int, rg: list[list[int]], order: list[int]) -> list[int]:
    """反图上按逆后序 DFS 染色，返回每个点所属强连通分量编号（从 0 连续）。"""
    comp = [-1] * n
    cid = 0
    for start in reversed(order):
        if comp[start] != -1:
            continue
        comp[start] = cid
        stack = [start]
        while stack:
            v = stack.pop()
            for w in rg[v]:
                if comp[w] == -1:          # 同一次反图 DFS 能到的点都属本分量
                    comp[w] = cid
                    stack.append(w)
        cid += 1
    return comp


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    g: list[list[int]] = [[] for _ in range(n)]
    rg: list[list[int]] = [[] for _ in range(n)]
    for _ in range(m):
        a, b = next(data) - 1, next(data) - 1  # 转 0 起下标
        g[a].append(b)
        rg[b].append(a)

    comp = assign_components(n, rg, postorder(n, g))

    # 缩点 DAG 中出度为 0 的分量才能被全员认可；答案 = 唯一汇点分量的大小
    has_out = {comp[u] for u, vs in enumerate(g) for v in vs if comp[v] != comp[u]}
    sinks = {cid for cid in range(max(comp) + 1)} - has_out
    popular = next(iter(sinks)) if len(sinks) == 1 else -1
    print(sum(1 for c in comp if c == popular) if popular != -1 else 0)


if __name__ == "__main__":
    solve()
