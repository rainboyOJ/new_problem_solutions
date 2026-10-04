#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 20:05
# update_at: 2026-09-30 20:05

import sys


def tree_dp(
    n: int, adj: list[list[int]], root: int = 0
) -> tuple[list[int], list[int], list[int], int]:
    """通过两遍树形 DP 计算每个节点向下最长/次长链、向上最长链及树的直径。"""
    parent = [-1] * n
    order = [root] * n
    head, tail = 0, 1
    while head < tail:
        u = order[head]
        head += 1
        for v in adj[u]:
            if v != parent[u]:
                parent[v] = u
                order[tail] = v
                tail += 1

    d1, d2, c1 = [0] * n, [0] * n, [-1] * n
    for u in reversed(order):
        p = parent[u]
        for v in adj[u]:
            if v != p and (w := d1[v] + 1) > d1[u]:
                d2[u], d1[u], c1[u] = d1[u], w, v
            elif v != p and w > d2[u]:
                d2[u] = w

    up = [0] * n
    for u in order:
        p, up_u, d1_u, d2_u, c1_u = parent[u], up[u], d1[u], d2[u], c1[u]
        for v in adj[u]:
            if v != p:
                best_down = d2_u if c1_u == v else d1_u
                up[v] = max(up_u + 1, best_down + 1)

    diameter = max(d1[u] + up[u] for u in range(n))
    return d1, d2, up, diameter


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    tokens = [int(x) for x in data]
    if not tokens:
        return
    n = tokens[0]

    adj: list[list[int]] = [[] for _ in range(n)]
    it = iter(tokens[1:])
    for u, v in zip(it, it):
        adj[u].append(v)
        adj[v].append(u)

    d1, d2, up, diameter = tree_dp(n, adj)
    ans = [u for u in range(n) if d1[u] + max(up[u], d2[u]) == diameter]
    print('\n'.join(map(str, ans)))


if __name__ == "__main__":
    solve()
