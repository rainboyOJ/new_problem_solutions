#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-05-22 19:17
# update_at: 2026-05-22 19:17

import sys

# 题目数据 n <= 10^5，树高最大为 10^5，二进制倍增步长取 18 即可满足 2^17 <= 10^5 < 2^18
MAX_LOG = 18


def build_tree(n: int, edges: list[tuple[int, int]]) -> tuple[list[int], list[list[int]]]:
    """通过 BFS 遍历树，返回每个节点的深度深度表与倍增祖先表 up[k][u]。"""
    adj: list[list[int]] = [[] for _ in range(n + 1)]
    for u, v in edges:
        adj[u].append(v)
        adj[v].append(u)

    depth = [0] * (n + 1)
    up = [[0] * (n + 1) for _ in range(MAX_LOG)]

    # BFS 层次遍历定父子关系与深度，避免深递归爆栈
    depth[1] = 1
    queue = [1]
    order: list[int] = []
    for u in queue:
        order.append(u)
        for v in adj[u]:
            if v != up[0][u]:
                depth[v] = depth[u] + 1
                up[0][v] = u
                queue.append(v)

    # 倍增预处理 2^k 级祖先表
    for k in range(1, MAX_LOG):
        prev = up[k - 1]
        curr = up[k]
        for u in range(1, n + 1):
            curr[u] = prev[prev[u]]

    return depth, up


def get_lca(u: int, v: int, depth: list[int], up: list[list[int]]) -> int:
    """倍增求树上任意两点 u, v 的最近公共祖先 (LCA)。"""
    if depth[u] < depth[v]:
        u, v = v, u

    # 1. 提升较深节点至同一深度
    diff = depth[u] - depth[v]
    for k in range(MAX_LOG):
        if diff >> k & 1:
            u = up[k][u]

    if u == v:
        return u

    # 2. 同步向上倍增跳跃，直到两者的父节点相同
    for k in reversed(range(MAX_LOG)):
        if up[k][u] != up[k][v]:
            u, v = up[k][u], up[k][v]

    return up[0][u]


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    try:
        first = next(data)
    except StopIteration:
        return
    n = int(first)
    edges = [(int(next(data)), int(next(data))) for _ in range(n - 1)]

    depth, up = build_tree(n, edges)

    q = int(next(data))
    out: list[str] = []
    for _ in range(q):
        u, v = int(next(data)), int(next(data))
        lca = get_lca(u, v, depth, up)
        # 树上两点距离公式：dist(u, v) = depth[u] + depth[v] - 2 * depth[lca]
        dist = depth[u] + depth[v] - 2 * depth[lca]
        out.append(str(dist))

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
