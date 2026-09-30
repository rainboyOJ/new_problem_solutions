#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-04-19 20:00
# update_at: 2026-04-19 20:00

import sys
from collections.abc import Iterator


def tree_min_vertex_cover(n: int, adj: list[list[int]], root: int = 0) -> int:
    """求以 root 为根的树的最小点覆盖大小。

    dp[u][0]: u 处不放士兵时，覆盖 u 为根的子树所有边所需的最少士兵数。
              此时 u 的所有子节点 v 处必须都放士兵。
    dp[u][1]: u 处放士兵时，覆盖 u 为根的子树所有边所需的最少士兵数。
              此时每个子节点 v 可以放也可以不放，取 min(dp[v][0], dp[v][1])。
    使用拓扑/DFS 后序模拟树形 DP，避免深递归爆栈。
    """
    order: list[int] = []
    parent = [-1] * n
    stack = [root]

    # BFS/DFS 收集自顶向下访问顺序
    while stack:
        u = stack.pop()
        order.append(u)
        for v in adj[u]:
            if v != parent[u]:
                parent[v] = u
                stack.append(v)

    # dp[u] = [不选 u, 选 u]
    dp0 = [0] * n
    dp1 = [1] * n

    # 逆拓扑序（自底向上）转移
    for u in reversed(order):
        for v in adj[u]:
            if v != parent[u]:
                dp0[u] += dp1[v]
                dp1[u] += min(dp0[v], dp1[v])

    return min(dp0[root], dp1[root])


def solve() -> None:
    tokens: Iterator[int] = map(int, sys.stdin.buffer.read().split())
    try:
        n = next(tokens)
    except StopIteration:
        return

    adj: list[list[int]] = [[] for _ in range(n)]
    in_degree = [0] * n

    for _ in range(n):
        u = next(tokens)
        k = next(tokens)
        children = [next(tokens) for _ in range(k)]
        adj[u].extend(children)
        for v in children:
            in_degree[v] += 1
            adj[v].append(u)

    # 找到树的根节点（输入中给出的父指向子，入度为 0 的即为树根）
    # 若有多棵树或全双向，任意找一个作为根；这里输入给的是有向树边，入度为 0 的节点即为根
    root = 0
    for i in range(n):
        if in_degree[i] == 0:
            root = i
            break

    ans = tree_min_vertex_cover(n, adj, root)
    print(ans)


if __name__ == "__main__":
    solve()
