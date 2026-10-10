#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 11:30
# update_at: 2026-10-07 11:30

import sys


def bfs_order(adj: list[list[int]]) -> tuple[list[int], list[int]]:
    """以 1 为根做迭代 BFS，返回 (访问序 order, 父节点数组 parent)。

    order 保证父亲排在儿子之前；把它倒过来读，就是「儿子先于父亲」的自底向上序。
    用显式队列而非递归，避免 n = 2e5 的链形数据爆栈。
    """
    n = len(adj) - 1
    order = [1]
    parent = [0] * (n + 1)
    for u in order:                      # 边遍历边追加：list 迭代会看到新元素
        for v in adj[u]:
            if v != parent[u]:           # 树上唯一的已访邻点就是父亲
                parent[v] = u
                order.append(v)
    return order, parent


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    try:
        n = next(data)
    except StopIteration:                # 空输入
        return

    adj: list[list[int]] = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        a, b = next(data), next(data)
        adj[a].append(b)
        adj[b].append(a)

    matched = [False] * (n + 1)          # 该节点是否已被某条匹配边占用
    order, parent = bfs_order(adj)

    # 自底向上贪心：u 与父亲都还空着，就把边 (u, parent[u]) 配上
    ans = 0
    for u in reversed(order):
        p = parent[u]
        if p and not matched[u] and not matched[p]:
            matched[u] = matched[p] = True
            ans += 1

    print(ans)


if __name__ == "__main__":
    solve()
