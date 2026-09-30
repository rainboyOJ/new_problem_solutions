#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 15:45
# update_at: 2026-09-30 15:45

import sys


def tarjan_scc(n: int, adj: list[list[int]]) -> list[int]:
    """计算有向图每个节点的强连通分量编号（0-indexed）。"""
    dfn = [0] * (n + 1)
    low = [0] * (n + 1)
    scc = [0] * (n + 1)
    stk: list[int] = []
    in_stk = [False] * (n + 1)
    timer = scc_cnt = 0

    def dfs(u: int) -> None:
        nonlocal timer, scc_cnt
        timer += 1
        dfn[u] = low[u] = timer
        stk.append(u)
        in_stk[u] = True

        for v in adj[u]:
            if not dfn[v]:
                dfs(v)
                low[u] = min(low[u], low[v])
            elif in_stk[v]:
                low[u] = min(low[u], dfn[v])

        if low[u] == dfn[u]:
            while True:
                top = stk.pop()
                in_stk[top] = False
                scc[top] = scc_cnt
                if top == u:
                    break
            scc_cnt += 1

    for i in range(1, n + 1):
        if not dfn[i]:
            dfs(i)

    return scc, scc_cnt


def solve() -> None:
    tokens = iter(sys.stdin.read().split())
    try:
        n = int(next(tokens))
    except StopIteration:
        return

    adj = [[] for _ in range(n + 1)]
    for u in range(1, n + 1):
        while True:
            v = int(next(tokens))
            if v == 0:
                break
            adj[u].append(v)

    scc, scc_cnt = tarjan_scc(n, adj)

    if scc_cnt == 1:
        print(1)
        print(0)
        return

    # 统计缩点后 DAG 中各 SCC 的入度与出度
    in_deg = [0] * scc_cnt
    out_deg = [0] * scc_cnt
    for u in range(1, n + 1):
        for v in adj[u]:
            if scc[u] != scc[v]:
                in_deg[scc[v]] += 1
                out_deg[scc[u]] += 1

    zero_in = sum(1 for d in in_deg if d == 0)
    zero_out = sum(1 for d in out_deg if d == 0)

    print(zero_in)
    print(max(zero_in, zero_out))


if __name__ == "__main__":
    solve()
