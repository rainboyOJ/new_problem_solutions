#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 01:49
# update_at: 2026-10-08 01:55

import sys

MOD = 1000000007  # 答案取模
LOG = 17          # 倍增层数：2^17 = 131072 > 1e5

type Adj = list[list[int]]     # adj[x] = 与 x 相邻的所有点
type Table = list[list[int]]   # up[j][x] = x 的 2^j 级祖先，0 表示不存在


def build_tree(n: int, adj: Adj) -> tuple[list[int], list[int], list[int]]:
    """以 1 为根做 BFS，返回 (父亲数组, 深度数组, BFS 序)。

    order 边遍历边增长，等价于一个队列；树上除了父亲没有别的已访问邻居。
    """
    fa = [0] * (n + 1)
    dep = [0] * (n + 1)
    order = [1]
    for x in order:
        for y in adj[x]:
            if y != fa[x]:
                fa[y] = x
                dep[y] = dep[x] + 1
                order.append(y)
    return fa, dep, order


def prefix_sums(n: int, fa: list[int], order: list[int], adj: Adj) -> tuple[list[int], list[int]]:
    """返回 (pf, pg)：根到每个点的路径上「向上期望 f」「向下期望 g」之和。

    f[x] = deg[x] + Σ f[儿子]：从 x 出发首次走到父亲的期望步数；
    g[x] = g[fa] + f[fa] - f[x]：从父亲出发首次走到 x 的期望步数。
    """
    f = [len(adj[x]) for x in range(n + 1)]
    for x in reversed(order[1:]):        # 逆 BFS 序即自底向上
        f[fa[x]] += f[x]

    g = [0] * (n + 1)
    pf = [0] * (n + 1)
    pg = [0] * (n + 1)
    for x in order[1:]:                  # BFS 序即自顶向下
        p = fa[x]
        g[x] = g[p] + f[p] - f[x]
        pf[x] = pf[p] + f[x]
        pg[x] = pg[p] + g[x]
    return pf, pg


def build_up(fa: list[int], n: int) -> Table:
    """倍增表：up[j][x] 是 x 的 2^j 级祖先（0 表示不存在）。"""
    up: Table = [fa]                     # 第 0 层就是父亲数组本身，只读不改
    for _ in range(LOG):
        prev = up[-1]
        up.append([prev[prev[x]] for x in range(n + 1)])
    return up


def lca(u: int, v: int, dep: list[int], up: Table) -> int:
    """求 u、v 的最近公共祖先：先把深的拉到同深度，再一起倍增上跳。"""
    if dep[u] < dep[v]:
        u, v = v, u
    diff = dep[u] - dep[v]
    for j in range(LOG):
        if diff >> j & 1:
            u = up[j][u]
    if u == v:
        return u
    for j in range(LOG, -1, -1):
        if up[j][u] != up[j][v]:
            u, v = up[j][u], up[j][v]
    return up[0][u]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, q = next(data), next(data)

    adj: Adj = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        u, v = next(data), next(data)
        adj[u].append(v)
        adj[v].append(u)

    fa, dep, order = build_tree(n, adj)
    pf, pg = prefix_sums(n, fa, order, adj)
    up = build_up(fa, n)

    # u 向上走到 z=LCA，再向下走到 v：两段期望步数直接相加
    out: list[str] = []
    for _ in range(q):
        u, v = next(data), next(data)
        z = lca(u, v, dep, up)
        out.append((pf[u] - pf[z] + pg[v] - pg[z]) % MOD)

    sys.stdout.write('\n'.join(map(str, out)) + '\n')


if __name__ == "__main__":
    solve()
