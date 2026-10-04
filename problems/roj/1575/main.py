#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 19:30
# update_at: 2026-09-30 19:30

import sys
from functools import cache


def solve() -> None:
    data = list(map(int, sys.stdin.read().split()))
    if not data:
        return
    it = iter(data)
    n, q = next(it), next(it)

    adj: list[list[tuple[int, int]]] = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        u, v, w = next(it), next(it), next(it)
        adj[u].append((v, w))
        adj[v].append((u, w))

    # 构建二叉树有向结构：children[u] = [(v1, w1), (v2, w2)]
    children: list[list[tuple[int, int]]] = [[] for _ in range(n + 1)]
    visited = [False] * (n + 1)
    visited[1] = True
    queue = [1]
    for u in queue:
        for v, w in adj[u]:
            if not visited[v]:
                visited[v] = True
                children[u].append((v, w))
                queue.append(v)

    # 记忆化搜索：dfs(u, k) 表示在以 u 为根的子树中保留 k 条边能获得的最大苹果数
    @cache
    def dfs(u: int, k: int) -> int:
        """在以 u 为根的子树内保留 k 条边的最大权值和。"""
        if k == 0 or not children[u]:
            return 0

        # 根据题意分叉一定是两叉或 0 叉（叶子）
        (l, wl), (r, wr) = children[u]

        # 分三种情况：只选左、只选右、两边分配
        return max(
            dfs(l, k - 1) + wl,
            dfs(r, k - 1) + wr,
            max(
                (dfs(l, i) + wl + dfs(r, k - 2 - i) + wr for i in range(k - 1)),
                default=0,
            ),
        )

    print(dfs(1, q))


if __name__ == "__main__":
    solve()
