#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 17:47
# update_at: 2026-10-07 17:47

import sys
from collections import deque

type Graph = list[list[int]]  # 邻接表：graph[u] 是结点 u 的出边终点列表


def build_machine(t: int, pats: list[str]) -> tuple[list[list[int]], list[bool]]:
    """建禁止串的 AC 自动机，返回补齐后的转移表和「禁止」标记（已沿 fail 链传递）。"""
    nxt = [[0] * t]
    banned = [False]
    for pat in pats:
        u = 0
        for ch in pat:
            c = ord(ch) - 97
            if nxt[u][c] == 0:
                nxt[u][c] = len(nxt)
                nxt.append([0] * t)
                banned.append(False)
            u = nxt[u][c]
        banned[u] = True

    fail = [0] * len(nxt)
    que = deque(c for c in nxt[0] if c)  # 根的直接儿子（0 表示根本没有这个儿子）
    while que:
        u = que.popleft()
        banned[u] = banned[u] or banned[fail[u]]  # 禁止标记沿 fail 链下传
        row = nxt[u]
        for c in range(t):
            if row[c]:
                fail[row[c]] = nxt[fail[u]][c]
                que.append(row[c])
            else:
                row[c] = nxt[fail[u]][c]  # 补齐转移：失配后该走到哪
    return nxt, banned


def strong_components(graph: Graph) -> list[int]:
    """Tarjan 求强连通分量（迭代版，避免深递归），返回每个结点所属的 SCC 编号。"""
    m = len(graph)
    dfn = [-1] * m  # -1 表示还没访问过
    low = [0] * m
    comp = [-1] * m
    on_stack = [False] * m
    stack: list[int] = []  # Tarjan 栈
    clock = 0
    comp_cnt = 0

    for root in range(m):
        if dfn[root] >= 0:
            continue
        work = [(root, 0)]  # (结点, 下一条要看的出边下标)
        while work:
            u, i = work[-1]
            if i == 0:
                dfn[u] = low[u] = clock
                clock += 1
                stack.append(u)
                on_stack[u] = True
            if i < len(graph[u]):
                work[-1] = (u, i + 1)
                v = graph[u][i]
                if dfn[v] < 0:
                    work.append((v, 0))
                elif on_stack[v]:
                    low[u] = min(low[u], dfn[v])
            else:
                work.pop()
                if low[u] == dfn[u]:  # u 是这个 SCC 里第一个被访问的结点
                    while True:
                        w = stack.pop()
                        on_stack[w] = False
                        comp[w] = comp_cnt
                        if w == u:
                            break
                    comp_cnt += 1
                if work:
                    p = work[-1][0]
                    low[p] = min(low[p], low[u])
    return comp


def count_chains(t: int, pats: list[str]) -> int:
    """统计两端都无限、平移视为同一条的合法链数量；有无穷多条时返回 -1。"""
    nxt, banned = build_machine(t, pats)
    # 只有「非禁止结点 + 非禁止转移」上的双无限路径才是合法链
    graph: Graph = [
        [v for v in nxt[u] if not banned[v]] if not banned[u] else [] for u in range(len(nxt))
    ]
    comp = strong_components(graph)
    size = [0] * (max(comp) + 1)  # 每个 SCC 的结点数
    inner = [0] * (max(comp) + 1)  # 每个 SCC 的内部边数
    for u in range(len(nxt)):
        if banned[u]:
            continue
        size[comp[u]] += 1
        inner[comp[u]] += sum(1 for v in graph[u] if comp[v] == comp[u])

    # SCC 是简单环 ⟺ 内部边数等于结点数；多出来的边意味着这个 SCC 自己就能造出无穷多条链
    if any(inner[c] > size[c] for c in range(len(size))):
        return -1
    is_cycle = [size[c] > 0 and inner[c] == size[c] for c in range(len(size))]

    out: Graph = [[] for _ in size]
    indeg = [0] * len(size)
    for u in range(len(nxt)):
        if banned[u]:
            continue
        for v in graph[u]:
            if comp[u] != comp[v]:
                out[comp[u]].append(comp[v])  # 缩点 DAG 保留重边：不同转移是不同的链
                indeg[comp[v]] += 1

    # 链 = 「环 SCC 起 + DAG 有限路径 + 环 SCC 收」，按拓扑序数路径
    path_cnt = [0] * len(size)  # 从某个环 SCC 出发、终点是这个 SCC 的路径条数
    cycle_on_path = [0] * len(size)  # 这些路径上环 SCC 个数的最大值
    que = deque(c for c in range(len(size)) if indeg[c] == 0)
    for c in que:
        cycle_on_path[c] = 1 if is_cycle[c] else 0  # 路径可以就从自己这个环开始
    while que:
        u = que.popleft()
        if cycle_on_path[u] >= 3:  # 夹在中间的环 SCC 能绕任意圈：无穷多条
            return -1
        if is_cycle[u]:
            path_cnt[u] += 1  # 长度 0 的路径：自己就是一个环
        for v in out[u]:
            path_cnt[v] += path_cnt[u]
            cycle_on_path[v] = max(cycle_on_path[v], cycle_on_path[u] + (1 if is_cycle[v] else 0))
            indeg[v] -= 1
            if indeg[v] == 0:
                que.append(v)
    return sum(path_cnt[c] for c in range(len(size)) if is_cycle[c])


def solve() -> None:
    tokens = iter(sys.stdin.buffer.read().split())
    t = int(next(tokens))
    n = int(next(tokens))
    pats = [next(tokens).decode() for _ in range(n)]
    print(count_chains(t, pats))


if __name__ == "__main__":
    solve()
