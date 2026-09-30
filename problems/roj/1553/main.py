#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 17:43
# update_at: 2026-09-30 17:43

import sys

LOG = 17  # 倍增上跳层数：2^17 = 131072 > N 上限 1e5


def lca(u: int, v: int, depth: list[int], up: list[list[int]]) -> int:
    """倍增求 u、v 的最近公共祖先。"""
    if depth[u] < depth[v]:
        u, v = v, u
    # 先把更深的 u 抬到与 v 同一深度
    d = depth[u] - depth[v]
    for k in range(LOG):
        if d >> k & 1:
            u = up[k][u]
    if u == v:
        return u
    # 两者不同则同步上跳，跳到 LCA 的正下方
    for k in range(LOG - 1, -1, -1):
        if up[k][u] != up[k][v]:
            u, v = up[k][u], up[k][v]
    return up[0][u]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    # 主要边构成树：无向邻接表
    g: list[list[int]] = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        a, b = next(data), next(data)
        g[a].append(b)
        g[b].append(a)

    # 以 1 为根迭代 DFS（避免深递归）：记父亲、深度与先根顺序
    root = 1
    parent = [0] * (n + 1)
    parent[root] = root
    depth = [0] * (n + 1)
    order: list[int] = []
    stack = [root]
    while stack:
        u = stack.pop()
        order.append(u)
        for v in g[u]:
            if v != parent[u]:
                parent[v] = u
                depth[v] = depth[u] + 1
                stack.append(v)

    # 倍增表：up[k][v] 是 v 的 2^k 级祖先；先根顺序保证父亲先于孩子处理
    up = [[0] * (n + 1) for _ in range(LOG)]
    up[0] = parent[:]
    for k in range(1, LOG):
        prev, cur = up[k - 1], up[k]
        for v in order:
            cur[v] = prev[prev[v]]

    # 树上差分：一条附加边 (u, v) 使路径上每条主要边的跨越计数 +1
    diff = [0] * (n + 1)
    for _ in range(m):
        u, v = next(data), next(data)
        w = lca(u, v, depth, up)
        diff[u] += 1
        diff[v] += 1
        diff[w] -= 2

    # 后序累加得到每条主要边的跨越计数 c，按 c 统计方案数
    ans = 0
    for u in reversed(order):
        if u == root:
            continue
        c = diff[u]  # 边 (parent[u], u) 被多少条附加边跨越
        ans += m if c == 0 else (1 if c == 1 else 0)
        diff[parent[u]] += c  # 计数并入父边

    print(ans)


if __name__ == "__main__":
    solve()
