#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 16:02
# update_at: 2026-09-30 16:02

import sys


def find_blocks(adj: list[list[tuple[int, int]]]) -> tuple[list[bool], list[set[int]]]:
    """Tarjan 求割点与点双连通分量（迭代版）：返回割点标记与各分量的顶点集合。"""
    n = len(adj)
    dfn = [0] * n          # DFS 编号，0 表示未访问
    low = [0] * n          # 子树经回边能到达的最小 DFS 编号
    cut = [False] * n      # 顶点是否为割点
    comps: list[set[int]] = []
    edge_stack: list[tuple[int, int]] = []      # 边栈：按序收集当前路径上的边
    clock = 0
    # DFS 栈三项：顶点、进入它的父边 id、下一条待检查的邻边位置（避免递归爆栈）
    dfs: list[list[int]] = []

    for root in range(n):
        if dfn[root]:
            continue
        clock += 1
        dfn[root] = low[root] = clock
        dfs.append([root, -1, 0])
        child_cnt = 0                          # 根的孩子数：大于 1 才是割点
        while dfs:
            u, parent_eid, i = dfs[-1]
            if i < len(adj[u]):
                dfs[-1][2] = i + 1
                v, eid = adj[u][i]
                if eid == parent_eid:          # 原路返回的树边不重复处理
                    continue
                if not dfn[v]:                 # 树边：向下展开
                    edge_stack.append((u, v))
                    clock += 1
                    dfn[v] = low[v] = clock
                    dfs.append([v, eid, 0])
                    if u == root:
                        child_cnt += 1
                elif dfn[v] < dfn[u]:          # 回边：只在编号大的一端入栈
                    edge_stack.append((u, v))
                    low[u] = min(low[u], dfn[v])
            else:
                dfs.pop()                      # u 全部邻边走完，向父节点回传 low
                if not dfs:
                    continue
                p = dfs[-1][0]
                low[p] = min(low[p], low[u])
                if low[u] >= dfn[p]:           # p 下方闭合出一个点双，弹出其边
                    block: set[int] = set()
                    while True:
                        a, b = edge_stack.pop()
                        block.add(a)
                        block.add(b)
                        if {a, b} == {u, p}:
                            break
                    comps.append(block)
                    if len(dfs) > 1:           # 根的割点判定在循环外按孩子数决定
                        cut[p] = True
        cut[root] = child_cnt > 1

    return cut, comps


def count_exits(cut: list[bool], comps: list[set[int]]) -> tuple[int, int]:
    """统计最少出口数与方案数：叶子分量出 1 个出口，无割点分量出 2 个。"""
    need = 0
    ways = 1
    for block in comps:
        size = len(block)
        cut_cnt = sum(cut[v] for v in block)
        if cut_cnt == 0:        # 整个连通块就是点双：任取两个顶点建出口
            need += 2
            ways *= size * (size - 1) // 2
        elif cut_cnt == 1:      # 叶子分量：出口必须建在非割点上，选一个即可
            need += 1
            ways *= size - 1
        # 含两个及以上割点的分量：割点坍塌后仍能绕行，无需出口
    return need, ways


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    case_no = 0

    for tunnel_cnt in data:               # 题目以 0 结尾
        if tunnel_cnt == 0:
            break
        edges = [(next(data), next(data)) for _ in range(tunnel_cnt)]

        # 顶点编号不连续，压缩成 0 基下标；边带 id 以便区分树边与父边的平行边
        verts = {v: i for i, v in enumerate({x for e in edges for x in e})}
        adj: list[list[tuple[int, int]]] = [[] for _ in verts]
        for eid, (a, b) in enumerate(edges):
            u, v = verts[a], verts[b]
            adj[u].append((v, eid))
            adj[v].append((u, eid))

        cut, comps = find_blocks(adj)
        need, ways = count_exits(cut, comps)
        case_no += 1
        out.append(f"Case {case_no}: {need} {ways}")

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
