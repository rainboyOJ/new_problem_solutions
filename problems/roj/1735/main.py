#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 20:26
# update_at: 2026-10-07 20:26

import sys

# 边弧编号约定：无向边 i 拆成弧 2i（u->v）与 2i+1（v->u），于是 e ^ 1 恒为反向弧，
# 「跳过父边」只要比较 e == (fe ^ 1)；根的 fe 用 -1，因为 -1 ^ 1 = -2 不是合法弧号。
type Adj = list[list[int]]  # adj[u] = 从 u 出发的弧编号列表


def count_edges(n: int, adj: Adj, arc_to: list[int]) -> tuple[int, int]:
    """Tarjan 点双；返回 (桥数, 落在「边数 > 点数」块内的边数)。

    桥 = 不在任何简单环上的边（low[u] > dfn[父]）；块内边数 > 点数时块必含
    >= 2 个环且每条边都至少属于两个简单环，把这些块的边数累加即为第二个答案。
    """
    dfn = [0] * n
    low = [0] * n
    vmark = [0] * n     # 统计块内点数的去重标记：值等于当前块号表示本块内已数过
    estack: list[int] = []  # 边栈：每弹空一次得到一个点双
    fu = [0] * n        # 迭代 dfs 的帧：当前点
    fptr = [0] * n      # 帧内游标：已处理到邻接表第几条弧
    ffe = [-1] * n      # 帧的入边编号，-1 表示该帧是根（无父边）
    ans1 = ans2 = 0
    timer = 0
    blk = 0

    for s in range(n):
        if dfn[s]:
            continue
        timer += 1
        dfn[s] = low[s] = timer
        top = 0
        fu[0], fptr[0], ffe[0] = s, 0, -1
        while top >= 0:                      # 显式栈 dfs：深链可达 1e4，不用递归
            u = fu[top]
            arcs = adj[u]
            pos = fptr[top]
            if pos < len(arcs):
                fptr[top] = pos + 1
                e = arcs[pos]
                is_parent_arc = e == (ffe[top] ^ 1)  # 用弧号判父边：反向弧恒为 e ^ 1
                if is_parent_arc:
                    continue
                v = arc_to[e]
                if dfn[v] == 0:              # 树边：入栈后进入 v
                    estack.append(e)
                    timer += 1
                    dfn[v] = low[v] = timer
                    top += 1
                    fu[top], fptr[top], ffe[top] = v, 0, e
                elif dfn[v] < dfn[u]:        # 回边：只从较深的一端入栈一次
                    estack.append(e)
                    if dfn[v] < low[u]:
                        low[u] = dfn[v]
            else:
                fe = ffe[top]
                top -= 1                     # u 的邻接表走完，弹出 u
                if fe < 0:                   # 根：它的块已由子节点返回时全部弹空
                    continue
                parent = fu[top]
                if low[u] < low[parent]:
                    low[parent] = low[u]
                if low[u] >= dfn[parent]:    # 找到一个点双，它含父边 fe
                    if low[u] > dfn[parent]:
                        ans1 += 1            # 父边是桥
                    blk += 1
                    ecnt = vcnt = 0
                    while True:
                        e = estack.pop()
                        ecnt += 1
                        a, b = arc_to[e ^ 1], arc_to[e]  # e 的起点、终点
                        if vmark[a] != blk:
                            vmark[a] = blk
                            vcnt += 1
                        if vmark[b] != blk:
                            vmark[b] = blk
                            vcnt += 1
                        if e == fe:
                            break
                    if ecnt > vcnt:
                        ans2 += ecnt
    return ans1, ans2


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    while True:
        n, m = next(data), next(data)
        if n == 0 and m == 0:                # 输入结束
            break
        arc_to = [0] * (2 * m)
        adj: Adj = [[] for _ in range(n)]
        for i in range(m):
            u, v = next(data), next(data)
            arc_to[2 * i], arc_to[2 * i + 1] = v, u
            adj[u].append(2 * i)
            adj[v].append(2 * i + 1)
        ans1, ans2 = count_edges(n, adj, arc_to)
        out.append(f"{ans1} {ans2}")
    print("\n".join(out))


if __name__ == "__main__":
    solve()
