#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 16:20
# update_at: 2026-09-30 16:29

import sys

NONE = 0  # 点编号从 1 开始，0 既是"没有父点"也天然是合法的列表越界哨兵


def tarjan(adj: list[list[int]], n: int) -> tuple[list[int], list[int], list[int]]:
    """迭代 Tarjan，返回长度 n+1 的 dfn / low / parent（下标 0 空着不用）。"""
    dfn, low, parent = [0] * (n + 1), [0] * (n + 1), [0] * (n + 1)
    timer = 0
    for root in range(1, n + 1):
        if dfn[root]:                                    # 图可能不连通，逐块起搜
            continue
        timer += 1
        dfn[root] = low[root] = timer
        stack = [(root, 0)]                              # (点, 下一个待看的邻边下标)
        while stack:
            u, i = stack[-1]
            if i < len(adj[u]):
                stack[-1] = (u, i + 1)
                v = adj[u][i]
                if dfn[v] == 0:
                    timer += 1
                    dfn[v] = low[v] = timer
                    parent[v] = u
                    stack.append((v, 0))
                elif v != parent[u]:                     # 回边；父边不参与 low 的松弛
                    low[u] = min(low[u], dfn[v])
            else:
                stack.pop()
                p = parent[u]
                if p != NONE:
                    low[p] = min(low[p], low[u])         # 出栈时把子点的 low 回传
    return dfn, low, parent


def block_squares(dfn: list[int], low: list[int], parent: list[int], n: int) -> list[int]:
    """sq[u] = 删掉 u 后各连通块大小的平方和（不含 u 自己那一份）。

    按 dfn 从大到小遍历，等价于 DFS 出栈顺序：儿子一定比父亲先被处理，
    所以子树大小能直接往父亲身上累加，不需要额外的回溯栈。
    """
    sq = [0] * (n + 1)
    size = [1] * (n + 1)
    cut = [0] * (n + 1)                                  # 已被 u 切出的子树大小之和
    for u in sorted(range(1, n + 1), key=dfn.__getitem__, reverse=True):
        p = parent[u]
        if p == NONE:
            continue
        if low[u] >= dfn[p]:                             # 子树 u 被 p 整块切出去
            sq[p] += size[u] ** 2
            cut[p] += size[u]
        size[p] += size[u]
    for u in range(1, n + 1):
        sq[u] += (n - 1 - cut[u]) ** 2                   # 祖先方向剩下的点合成最后一块
    return sq


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    n, m = int(data[0]), int(data[1])
    adj: list[list[int]] = [[] for _ in range(n + 1)]
    for i in range(2, 2 + 2 * m, 2):
        u, v = int(data[i]), int(data[i + 1])
        adj[u].append(v)
        adj[v].append(u)
    dfn, low, parent = tarjan(adj, n)
    sq = block_squares(dfn, low, parent, n)
    # 跨块点对 = (n-1)^2 - sq[u]（有序）；再加上 u 与其余 n-1 个点各自失联。
    print('\n'.join(str((n - 1) ** 2 - sq[u] + 2 * (n - 1)) for u in range(1, n + 1)))


if __name__ == "__main__":
    solve()
