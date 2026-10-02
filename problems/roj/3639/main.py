#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 12:11
# update_at: 2026-10-02 12:11

import sys
from bisect import bisect_left, bisect_right
from collections import defaultdict


def find(anc: list[int], x: int) -> int:
    """并查集查找（路径折半）：x 当前能摸到的最高"已结束子树"代表。"""
    while anc[x] != x:
        anc[x] = anc[anc[x]]
        x = anc[x]
    return x


def subtree_count(buckets: defaultdict[int, list[int]], key: int, lo: int, hi: int) -> int:
    """buckets[key] 里 tin 落在 [lo, hi] 的个数：u 的子树内有多少个 key 类标记。"""
    marks = buckets.get(key)
    if marks is None:
        return 0
    return bisect_right(marks, hi) - bisect_left(marks, lo)


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n = int(next(data)); m = int(next(data))

    adj: list[list[int]] = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        u = int(next(data)); v = int(next(data))
        adj[u].append(v); adj[v].append(u)

    weight = [0] + [int(next(data)) for _ in range(n)]  # W_j：结点 j 的观察时刻

    # 每条路径拆成三段事件：上坡差分 +，折点父亲差分 -；下坡差分 +，折点差分 -
    s = [0] * m; t = [0] * m; lca = [0] * m
    at_start: list[list[int]] = [[] for _ in range(n + 1)]  # Tarjan 询问挂在两端点
    at_term: list[list[int]] = [[] for _ in range(n + 1)]
    for i in range(m):
        a = int(next(data)); b = int(next(data))
        s[i] = a; t[i] = b
        at_start[a].append(i); at_term[b].append(i)

    # 迭代 DFS 得真先序 order；回溯时把子树并入并查集（Tarjan 离线 LCA）
    parent = [0] * (n + 1)
    depth = [0] * (n + 1)
    anc = list(range(n + 1))
    visited = [False] * (n + 1)
    it: list = [None] * (n + 1)  # 每个点自己的邻居迭代器，代替递归
    order: list[int] = []

    def walk(u: int) -> None:
        """进入 u（真先序）；若某条询问的另一端已进入，立刻取 LCA。"""
        order.append(u)
        for i in at_start[u]:
            other = t[i]
            if visited[other]:
                lca[i] = find(anc, other)
        for i in at_term[u]:
            other = s[i]
            if visited[other]:
                lca[i] = find(anc, other)

    visited[1] = True
    walk(1)
    it[1] = iter(adj[1])
    stack = [1]
    while stack:
        u = stack[-1]
        pushed = False
        for v in it[u]:
            if not visited[v]:
                visited[v] = True
                parent[v] = u
                depth[v] = depth[u] + 1
                it[v] = iter(adj[v])
                walk(v)
                stack.append(v)
                pushed = True
                break
        if not pushed:  # u 的子树结束：把 u 向父亲收拢
            stack.pop()
            if u != 1:
                anc[find(anc, u)] = parent[u]

    tin = [0] * (n + 1)  # 先序时间戳，子树 = 一段连续区间
    for idx, u in enumerate(order):
        tin[u] = idx
    size = [1] * (n + 1)
    for u in reversed(order):  # 逆先序保证算父亲时孩子已齐
        if u != 1:
            size[parent[u]] += size[u]

    # 两类差分，键是"观察等式"里的常量，桶里存路径端点的 tin：
    # 上坡（S..L，含两端）标记 dep[S]；下坡（(L..T]）标记 dep[S] - 2*dep[L]
    up_add: defaultdict[int, list[int]] = defaultdict(list)
    up_sub: defaultdict[int, list[int]] = defaultdict(list)
    down_add: defaultdict[int, list[int]] = defaultdict(list)
    down_sub: defaultdict[int, list[int]] = defaultdict(list)
    for i in range(m):
        d = depth[s[i]]
        k = d - 2 * depth[lca[i]]  # 下坡等式的常量
        up_add[d].append(tin[s[i]])
        down_add[k].append(tin[t[i]])
        if parent[lca[i]]:  # 上坡去掉折点：减在折点父亲处（根没有父亲，标记自然丢失）
            up_sub[d].append(tin[parent[lca[i]]])
        down_sub[k].append(tin[lca[i]])

    for buckets in (up_add, up_sub, down_add, down_sub):
        for marks in buckets.values():
            marks.sort()  # 排序后子树计数变成一次二分

    ans = [0] * (n + 1)
    for u in range(1, n + 1):
        du = depth[u]
        lo = tin[u]; hi = lo + size[u] - 1
        ans[u] = (
            subtree_count(up_add, du + weight[u], lo, hi)
            + subtree_count(down_add, weight[u] - du, lo, hi)
            - subtree_count(up_sub, du + weight[u], lo, hi)
            - subtree_count(down_sub, weight[u] - du, lo, hi)
        )

    print(' '.join(map(str, ans[1:])))


if __name__ == "__main__":
    solve()
