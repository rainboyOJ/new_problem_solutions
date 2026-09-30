#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-04-19 12:00
# update_at: 2026-04-19 12:00

import sys
from collections import defaultdict, deque


def find_root(parent: dict[int, int], x: int) -> int:
    """并查集查找代表元（带路径压缩）。"""
    while parent[x] != x:
        parent[x] = parent[parent[x]]
        x = parent[x]
    return x


def union_sets(parent: dict[int, int], x: int, y: int) -> None:
    """合并两个节点所在的连通分量。"""
    root_x, root_y = find_root(parent, x), find_root(parent, y)
    if root_x != root_y:
        parent[root_x] = root_y


def count_extra_edges(in_deg: dict[int, int], out_deg: dict[int, int], nodes: list[int]) -> int:
    """计算单个弱连通块为满足欧拉路径需要补齐的额外有向边数。"""
    pos_diff = sum(max(0, out_deg[u] - in_deg[u]) for u in nodes)
    return max(1, pos_diff)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    try:
        m = next(data)
    except StopIteration:
        return

    in_deg: dict[int, int] = defaultdict(int)
    out_deg: dict[int, int] = defaultdict(int)
    parent: dict[int, int] = {}
    edges_count = m

    for _ in range(m):
        u, v = next(data), next(data)
        out_deg[u] += 1
        in_deg[v] += 1
        parent.setdefault(u, u)
        parent.setdefault(v, v)
        union_sets(parent, u, v)

    components: dict[int, list[int]] = defaultdict(list)
    for node in parent:
        components[find_root(parent, node)].append(node)

    extra_edges = sum(count_extra_edges(in_deg, out_deg, nodes) for nodes in components.values())
    print(edges_count + extra_edges)


if __name__ == "__main__":
    solve()
