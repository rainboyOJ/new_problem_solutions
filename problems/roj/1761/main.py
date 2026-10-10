#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 22:38
# update_at: 2026-10-07 22:38

import sys

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Adj = list[list[int]]    # 生成树的邻接表：adj[x] 是 x 的所有邻居
type Sparse = list[list[int]] # 欧拉序上的 RMQ 稀疏表，第 k 层窗口长 2^k，存深度最小的节点
type Lca = tuple[list[int], Sparse, list[int], list[int]]  # (欧拉序, 稀疏表, 首次出现位置, 深度)


def rooted_tree(adj: Adj, n: int) -> tuple[list[int], list[int], list[int]]:
    """以 1 为根 BFS，返回 (父亲, 深度, BFS 序)；BFS 序倒着扫就是自底向上的累加顺序。"""
    par = [0] * (n + 1)
    dep = [0] * (n + 1)
    order = [1]
    for u in order:                     # 边遍历边追加，等价于一个队列
        for v in adj[u]:
            if v != par[u]:             # 树里除父亲外都是孩子，不需要额外判重
                par[v] = u
                dep[v] = dep[u] + 1
                order.append(v)
    return par, dep, order


def euler_tour(adj: Adj, par: list[int], n: int) -> tuple[list[int], list[int]]:
    """迭代 DFS 求欧拉序（长 2n-1）与每个节点首次出现的位置。

    进入节点与回退到父节点各记一笔，于是 u、v 的 LCA 恰好是欧拉序上
    first[u]..first[v] 这段区间里深度最小的那个节点。
    """
    euler = [1]
    first = [0] * (n + 1)
    ptr = [0] * (n + 1)                 # ptr[x] 指向 adj[x] 里下一个待访问的邻居
    stack = [1]
    while stack:
        u = stack[-1]
        if ptr[u] < len(adj[u]):
            v = adj[u][ptr[u]]
            ptr[u] += 1
            if v != par[u]:
                first[v] = len(euler)   # 树的 DFS 里 v 只可能由父亲首次走到
                euler.append(v)
                stack.append(v)
        else:
            stack.pop()
            if stack:
                euler.append(stack[-1]) # 回退到父节点，再记一笔
    return euler, first


def rmq_table(euler: list[int], dep: list[int]) -> Sparse:
    """对欧拉序建稀疏表：第 k 层存窗口长 2^k 内深度最小的节点，供 O(1) 区间取最小。"""
    table: Sparse = [euler]             # 第 0 层窗口长 1，就是欧拉序本身
    while 1 << len(table) <= len(euler):
        prev = table[-1]
        half = 1 << (len(table) - 1)
        table.append([a if dep[a] < dep[b] else b for a, b in zip(prev, prev[half:])])
    return table


def cover_counts(eu: list[int], ev: list[int], lca: Lca) -> list[int]:
    """树上边差分：每条非树边 (u,v) 给 u-v 树上路径上的每条树边加一。

    树边 (par[x], x) 的值记在节点 x 上，于是每条非树边做
    diff[u]++, diff[v]++, diff[LCA] -= 2；之后按 BFS 序倒着做子树和，
    节点 x 的值就是覆盖树边 (par[x], x) 的非树边条数。
    """
    euler, table, first, dep = lca
    diff = [0] * len(dep)
    for u, v in zip(eu, ev):
        l, r = first[u], first[v]
        if l > r:
            l, r = r, l
        k = (r - l + 1).bit_length() - 1   # 覆盖 [l, r] 的层号：2^k <= r-l+1
        row = table[k]
        a = row[l]
        b = row[r - (1 << k) + 1]
        w = a if dep[a] < dep[b] else b    # 区间内深度最小的节点就是 LCA
        diff[u] += 1
        diff[v] += 1
        diff[w] -= 2
    return diff


def min_cut_answer(diff: list[int], order: list[int], par: list[int]) -> int:
    """恰好含一条树边的割的最小边数：树边 (par[x], x) 的覆盖数 + 1，取最小。

    逆 BFS 序做子树和（孩子的值先并给父亲）之后，diff[x] 就是跨过树边
    (par[x], x) 的非树边条数，于是该割的边数 = 覆盖数 + 1。
    """
    for x in reversed(order[1:]):
        diff[par[x]] += diff[x]
    best = min((diff[x] for x in order[1:]), default=-1)  # 无树边时（约束外）输出 0
    return best + 1


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)

    for _ in range(T):
        n, m = next(data), next(data)

        adj: Adj = [[] for _ in range(n + 1)]
        for _ in range(n - 1):              # 先读生成树 T 的 N-1 条边
            u, v = next(data), next(data)
            adj[u].append(v)
            adj[v].append(u)

        extra = m - n + 1                   # 题面：其余 M-N+1 条边不在 T 中
        eu = [0] * extra
        ev = [0] * extra
        for i in range(extra):
            eu[i], ev[i] = next(data), next(data)

        par, dep, order = rooted_tree(adj, n)
        euler, first = euler_tour(adj, par, n)
        diff = cover_counts(eu, ev, (euler, rmq_table(euler, dep), first, dep))
        out.append(str(min_cut_answer(diff, order, par)))

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
