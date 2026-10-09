#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 20:47
# update_at: 2026-10-09 21:05

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data, None)
    if n is None:
        return
    m = next(data)

    adj = [[] for _ in range(n + 1)]
    for _ in range(m):
        u = next(data)
        adj[u].append(next(data))

    dfn = [0] * (n + 1)
    low = [0] * (n + 1)
    in_stk = [False] * (n + 1)
    stk = []
    timer = 0
    scc = [0] * (n + 1)
    scc_cnt = 0
    scc_sz = []

    # 迭代版 Tarjan：用显式栈代替递归，避免 n=2000 的深链爆栈
    for root in range(1, n + 1):
        if dfn[root]:
            continue
        work = [(root, 0)]
        while work:
            u, pi = work[-1]
            if pi == 0:
                timer += 1
                dfn[u] = low[u] = timer
                stk.append(u)
                in_stk[u] = True
            if pi < len(adj[u]):
                v = adj[u][pi]
                work[-1] = (u, pi + 1)
                if not dfn[v]:
                    work.append((v, 0))
                elif in_stk[v]:
                    if dfn[v] < low[u]:
                        low[u] = dfn[v]
            else:
                work.pop()
                if work:
                    p = work[-1][0]
                    if low[u] < low[p]:
                        low[p] = low[u]
                if dfn[u] == low[u]:
                    scc_cnt += 1
                    sz = 0
                    while True:
                        v = stk.pop()
                        in_stk[v] = False
                        scc[v] = scc_cnt
                        sz += 1
                        if v == u:
                            break
                    scc_sz.append(sz)

    dag = [[] for _ in range(scc_cnt + 1)]
    rev_dag = [[] for _ in range(scc_cnt + 1)]
    in_deg = [0] * (scc_cnt + 1)

    for u in range(1, n + 1):
        for v in adj[u]:
            su = scc[u]
            sv = scc[v]
            if su != sv:
                dag[su].append(sv)

    for i in range(1, scc_cnt + 1):
        dag[i] = list(set(dag[i]))
        for v in dag[i]:
            rev_dag[v].append(i)
            in_deg[v] += 1

    q = [i for i in range(1, scc_cnt + 1) if in_deg[i] == 0]
    topo = []
    head = 0
    while head < len(q):
        u = q[head]
        head += 1
        topo.append(u)
        for v in dag[u]:
            in_deg[v] -= 1
            if in_deg[v] == 0:
                q.append(v)

    # 位掩码可达性：第 i 位为 1 表示分量 i 在集合里（Python 大整数直接当位集用）
    # 下标 0 置 0（分量编号从 1 起，bit 0 永不参与交集，避免误取 scc_sz[-1]）
    reach = [0] + [1 << i for i in range(1, scc_cnt + 1)]
    reach_rev = [0] + [1 << i for i in range(1, scc_cnt + 1)]

    for u in reversed(topo):
        for v in dag[u]:
            reach[u] |= reach[v]

    for u in topo:
        for p in rev_dag[u]:
            reach_rev[u] |= reach_rev[p]

    max_ans = max(scc_sz, default=0)
    for u in range(1, scc_cnt + 1):
        for v in dag[u]:
            mask = reach[u] & reach_rev[v]
            cur = 0
            while mask:
                low_bit = mask & -mask
                cur += scc_sz[low_bit.bit_length() - 2]
                mask ^= low_bit
            if cur > max_ans:
                max_ans = cur

    print(max_ans)


if __name__ == '__main__':
    solve()