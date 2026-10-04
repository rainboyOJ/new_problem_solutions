#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 20:18
# update_at: 2026-09-30 20:25

from collections import deque
import sys

BLACK, WHITE, NONE = 0, 1, 2  # dp 状态：根到 u 路径上最后一个有色节点的颜色，NONE = 上方还没有有色节点


def min_coloring(adj: list[list[int]], color: list[int], root: int) -> int:
    """以 root 为根做树形 DP，返回让所有叶子 c_u 都成立的最少着色数。"""
    parent = [0] * len(adj)
    parent[root] = -1
    order = [root]
    q = deque([root])
    while q:  # 迭代建先父后子的顺序：深链也不爆栈
        u = q.popleft()
        for v in adj[u]:
            if not parent[v]:
                parent[v] = u
                q.append(v)
                order.append(v)

    dp: dict[int, tuple[int, int, int]] = {}
    for u in reversed(order):
        kids = [v for v in adj[u] if v != parent[u]]
        if not kids:  # 叶子：上方颜色不合要求就只能自己着色，上方没色更得着色
            dp[u] = (0 if color[u] == BLACK else 1,
                     0 if color[u] == WHITE else 1,
                     1)
            continue
        # u 不着色：子树各自沿用上方状态 u；u 着色：付 1 个代价，子树状态全换成 u 的颜色
        inherit = [sum(dp[v][s] for v in kids) for s in (BLACK, WHITE, NONE)]
        paint = (1 + sum(dp[v][BLACK] for v in kids),
                 1 + sum(dp[v][WHITE] for v in kids))
        dp[u] = tuple(min(paint[0], paint[1], inherit[s]) for s in (BLACK, WHITE, NONE))
    return dp[root][NONE]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    m, n = next(data), next(data)

    color = [0] * (m + 1)
    for leaf in range(1, n + 1):  # 前 n 个节点恰好是全部叶子，依次给出 c_u
        color[leaf] = next(data)

    adj: list[list[int]] = [[] for _ in range(m + 1)]
    for _ in range(m - 1):
        a, b = next(data), next(data)
        adj[a].append(b)
        adj[b].append(a)

    # 题目要求根的度数 > 1；答案与根的选取无关，任取一个满足条件的节点即可
    root = next(u for u in range(1, m + 1) if len(adj[u]) > 1)
    print(min_coloring(adj, color, root))


if __name__ == "__main__":
    solve()
