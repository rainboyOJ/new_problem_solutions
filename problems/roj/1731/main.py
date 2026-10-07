#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 20:29
# update_at: 2026-10-07 20:29

import sys

NO_BAN = -1  # 求「原图」时的 ban 取值：一条边都不删
ALL_EDGES = None  # 传给 flood 的 skip 参数：没有任何边被标成桥（全部边都保留）

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Csr = tuple[list[int], list[int], list[int], list[int]]  # CSR：区间起点 / 邻点 / 邻边号 / 度数
type EdgeList = list[tuple[int, int]]                         # 原始边表，下标就是边编号
type ClassCount = dict[int, int]                              # 等价类号 -> 该类里的点数
type ClassRank = dict[int, int]                               # (上一轮类号, 本轮分量号) 编成的复合键 -> 新类号


def build_csr(n: int, m: int, edges: EdgeList) -> Csr:
    """把边表压成 CSR：点 v 的邻边占下标区间 [start[v], start[v]+deg[v])，无向边登记两次。

    邻边存两份信息：另一端点 adj_v、原始边号 adj_e（判桥、删边都要按边号来）。
    """
    deg = [0] * (n + 2)
    for u, v in edges:
        deg[u] += 1
        deg[v] += 1
    start = [0] * (n + 2)
    total = 0
    for v in range(1, n + 1):
        start[v] = total
        total += deg[v]
    start[n + 1] = total
    adj_v = [0] * (2 * m)
    adj_e = [0] * (2 * m)
    pos = start[:]  # 写入游标，初值就是每个点区间的起点
    for e, (u, v) in enumerate(edges):
        adj_v[pos[u]], adj_e[pos[u]] = v, e
        pos[u] += 1
        adj_v[pos[v]], adj_e[pos[v]] = u, e
        pos[v] += 1
    return start, adj_v, adj_e, deg


def flood(csr: Csr, n: int, ban: int, skip: bytearray | None) -> list[int]:
    """忽略 skip 中标 1 的边与被删边 ban，用 flood-fill 给连通块编号。

    skip 为空时得到的就是普通连通分量编号（flow >= 1 的判据）；
    skip 是桥标记时，剩下的每个连通块就是一个边双连通分量（flow >= 2 的判据）。
    """
    start, adj_v, adj_e, deg = csr
    label = [0] * (n + 1)
    comp = 0
    for s in range(1, n + 1):
        if label[s]:
            continue
        comp += 1
        label[s] = comp
        st = [s]
        while st:
            u = st.pop()
            for i in range(start[u], start[u] + deg[u]):
                e = adj_e[i]
                removed = e == ban or (skip is not ALL_EDGES and skip[e])  # 被删边或桥
                if removed:
                    continue
                w = adj_v[i]
                if not label[w]:
                    label[w] = comp
                    st.append(w)
    return label


def two_ecc(csr: Csr, n: int, m: int, ban: int) -> list[int]:
    """删掉边 ban 后每个点所属的边双连通分量编号（ban = NO_BAN 表示不删边）。

    先迭代式 Tarjan 标出所有桥，再忽略桥与被删边 flood-fill，每块就是一个分量。
    写成迭代是为了躲开 Python 的递归深度限制——n = 3000 的链足以撑爆默认递归栈。
    """
    start, adj_v, adj_e, deg = csr
    dfn = [0] * (n + 1)   # Tarjan 时间戳，0 表示还没访问
    low = [0] * (n + 1)   # 追溯值：子树里能绕回的最早时间戳
    par = [-1] * (n + 1)  # 每个点是从父亲哪条边下来的，用来排除"原路返回"
    cur = start[:]        # 邻边游标：每个点已经扫到区间里的哪一个位置
    is_bridge = bytearray(m)
    vstk = [0] * (n + 1)  # DFS 顶点栈
    estk = [0] * (n + 1)  # 与顶点栈同高的入边栈：estk[top] 是 vstk[top] 的入边
    timer = 0
    for s in range(1, n + 1):  # 图可以不连通，逐分量起一次 DFS
        if dfn[s]:
            continue
        timer += 1
        dfn[s] = low[s] = timer
        vstk[0] = s
        estk[0] = -1
        top = 1
        while top:
            u = vstk[top - 1]
            i = cur[u]
            end = start[u] + deg[u]  # u 每轮都变，区间右端也要跟着重算
            while i < end and adj_e[i] == ban:  # 被删的边直接跳过
                i += 1
            cur[u] = i
            if i >= end:  # 回溯：u 的子树处理完毕，可以判桥了
                top -= 1
                if top:
                    p = vstk[top - 1]
                    if low[u] > dfn[p]:
                        is_bridge[estk[top]] = 1  # 树边 (p,u) 是桥
                    if low[u] < low[p]:
                        low[p] = low[u]
                continue
            cur[u] = i + 1
            e = adj_e[i]
            w = adj_v[i]
            if not dfn[w]:  # 树边：压栈，等回溯时判桥
                timer += 1
                dfn[w] = low[w] = timer
                par[w] = e
                vstk[top] = w
                estk[top] = e
                top += 1
                continue
            is_back_edge = e != par[u] and dfn[w] < low[u]  # 回边，且指向祖先
            if is_back_edge:
                low[u] = dfn[w]
    return flood(csr, n, ban, is_bridge)


def count_pairs(label: list[int]) -> int:
    """同一等价类内部的点对数之和，即 #{(i<j) : label[i] == label[j]}。

    label 的下标 0 是占位格（本题不用点 0），只统计 label[1..n]，
    否则占位格会被并进类号 0 的那一类，凭空多算出若干点对。
    """
    cnt: ClassCount = {}
    for x in label[1:]:
        cnt[x] = cnt.get(x, 0) + 1
    return sum(c * (c - 1) // 2 for c in cnt.values())


def count_flow3_pairs(csr: Csr, n: int, m: int, edges: EdgeList, bel0: list[int]) -> int:
    """flow >= 3 的点对数：删掉任意一条边后两点仍同属一个边双分量。

    删「桥」不会改变原图的边双划分（删边只会让划分变细、不可能合并，而桥不在任何
    非平凡块内部），所以只检验非桥边。每轮按 (上一轮类号, 本轮分量号) 把等价类细分
    一次——这类精化只分裂、不合并，跑完所有非桥边后同类的点对恰好就是 flow >= 3。

    没有非桥边就意味着原图是森林（每条边都是桥），删一条边必然切断，cnt3 = 0。
    """
    non_bridge = [e for e, (u, v) in enumerate(edges) if bel0[u] == bel0[v]]
    if not non_bridge:
        return 0
    cls = [0] * (n + 1)  # 初值全相同，是最粗的起点
    for ban in non_bridge:
        bel = two_ecc(csr, n, m, ban)
        rank: ClassRank = {}
        for v in range(1, n + 1):
            key = cls[v] * (n + 1) + bel[v]  # 拼成一个可哈希的二元组键
            if key not in rank:
                rank[key] = len(rank)
            cls[v] = rank[key]
        if len(rank) == n:  # 类已经全是单点，再细分也不会变回来（此时 cnt3 必为 0）
            break
    return count_pairs(cls)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    edges: EdgeList = [(next(data), next(data)) for _ in range(m)]
    csr = build_csr(n, m, edges)

    bel0 = two_ecc(csr, n, m, NO_BAN)  # 原图的边双划分，后两层都要用
    cnt1 = count_pairs(flood(csr, n, NO_BAN, ALL_EDGES))                      # 连通 = flow >= 1
    cnt2 = count_pairs(bel0)                                                  # 2-边连通 = flow >= 2
    cnt3 = count_flow3_pairs(csr, n, m, edges, bel0)                          # 待删边仍 2-边连通 = flow >= 3
    print(cnt1 + cnt2 + cnt3)


if __name__ == "__main__":
    solve()
