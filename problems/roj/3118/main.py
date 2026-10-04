#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 18:18
# update_at: 2026-10-01 18:27

import sys
from bisect import bisect_right


def count_le(sorted_dists: list[int], k: int) -> int:
    """统计有序数组里有多少对 j <= i 满足 dist[j] + dist[i] <= k（含 i = j 的自配对）。"""
    return sum(bisect_right(sorted_dists, k - d, 0, i + 1) for i, d in enumerate(sorted_dists))


def find_centroid(adj: list[list[tuple[int, int]]], removed: list[bool], root: int) -> int:
    """求 root 所在分量的重心：它删掉后，剩下的每块规模都不超过总量一半。"""
    n = len(adj)
    parent = [-1] * n
    parent[root] = root
    order = [root]
    for u in order:                                       # order 边遍历边增长，等价于手写栈
        for v, _ in adj[u]:
            if not removed[v] and v != parent[u]:
                parent[v] = u
                order.append(v)

    size = [0] * n
    for u in reversed(order):                             # 子节点一定排在父节点之后
        size[u] = 1
        for v, _ in adj[u]:
            if not removed[v] and parent[v] == u:
                size[u] += size[v]

    cent = root
    total = size[root]
    while True:
        heavy, best = -1, 0
        for v, _ in adj[cent]:
            if not removed[v] and parent[v] == cent and size[v] > best:
                heavy, best = v, size[v]
        if heavy < 0 or best * 2 <= total:                # 没有超过一半的重儿子：重心已找到
            return cent
        cent = heavy


def collect_by_subtree(
    adj: list[list[tuple[int, int]]], removed: list[bool], cent: int, k: int
) -> list[list[int]]:
    """从重心出发按子树收集距离（大于 k 的分支剪掉），sub[0] 是空占位，代表重心自身。"""
    sub: list[list[int]] = [[]]
    for v, w in adj[cent]:
        if removed[v]:
            continue
        dists: list[int] = []
        stack = [(v, cent, w)]
        while stack:
            u, p, d = stack.pop()
            if d > k:                                     # 权值非负，更深的点只会更远
                continue
            dists.append(d)
            stack += [(x, u, d + wx) for x, wx in adj[u] if x != p and not removed[x]]
        sub.append(sorted(dists))
    return sub


def divide(adj: list[list[tuple[int, int]]], k: int) -> int:
    """点分治：逐层在重心处用「汇总 - 各子树」容斥，返回合法点对数（含自配对）。"""
    n = len(adj)
    removed = [False] * n
    roots = [0]                                           # 待处理分量的代表点
    answer = 0

    while roots:
        root = roots.pop()
        if removed[root]:                                 # 该点已在更早的层里当过重心
            continue

        cent = find_centroid(adj, removed, root)
        sub = collect_by_subtree(adj, removed, cent, k)
        # 重心自身的距离 0 必 <= k，先加进汇总集合；同一子树内部的配对要在本层扣掉
        merged = sorted([0] + [d for ds in sub[1:] for d in ds])
        answer += count_le(merged, k) - sum(count_le(ds, k) for ds in sub[1:])

        removed[cent] = True                              # 分治层：删掉重心，邻居各代表一个新分量
        roots += [v for v, _ in adj[cent] if not removed[v]]

    return answer


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []

    while True:
        n, k = next(data), next(data)
        if n == 0 and k == 0:
            break

        adj: list[list[tuple[int, int]]] = [[] for _ in range(n)]
        for _ in range(n - 1):
            u, v, w = next(data), next(data), next(data)
            adj[u].append((v, w))
            adj[v].append((u, w))

        # 计数包含 x = y 的自配对，而路径要求两个节点不同，故每个点各减一次
        out.append(str(divide(adj, k) - n))

    print("\n".join(out))


if __name__ == "__main__":
    solve()
