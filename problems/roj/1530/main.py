#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-28 17:00
# update_at: 2026-09-28 17:00

import sys


def find(parent: list[int], x: int) -> int:
    """带路径压缩的并查集查找代表元。"""
    root = x
    while parent[root] >= 0:
        root = parent[root]
    curr = x
    while curr != root:
        nxt = parent[curr]
        if nxt < 0:
            break
        parent[curr] = root
        curr = nxt
    return root


def union(parent: list[int], x: int, y: int) -> None:
    """按秩合并两个集合。"""
    rx = find(parent, x)
    ry = find(parent, y)
    if rx == ry:
        return
    if parent[rx] < parent[ry]:  # rx 集合更大（负数绝对值更大）
        parent[rx] += parent[ry]
        parent[ry] = rx
    else:
        parent[ry] += parent[rx]
        parent[rx] = ry


def min_strokes_for_graph(n: int, edges: list[tuple[int, int]]) -> int:
    """计算遍历图中所有边所需的最少笔数。"""
    if not edges:
        return 0

    parent = [-1] * (n + 1)
    degree = [0] * (n + 1)

    for u, v in edges:
        degree[u] += 1
        degree[v] += 1
        union(parent, u, v)

    odd_counts: dict[int, int] = {}
    active_roots: set[int] = set()

    for i in range(1, n + 1):
        if degree[i] > 0:
            root = find(parent, i)
            active_roots.add(root)
            if degree[i] & 1:
                odd_counts[root] = odd_counts.get(root, 0) + 1

    total_strokes = sum(
        odd_counts[root] // 2 if odd_counts.get(root, 0) > 0 else 1
        for root in active_roots
    )
    return total_strokes


def solve() -> None:
    input_data = sys.stdin.buffer.read().split()
    if not input_data:
        return
    data_iter = iter(input_data)
    out: list[str] = []

    while True:
        try:
            n = int(next(data_iter))
            m = int(next(data_iter))
        except StopIteration:
            break

        edges = [(int(next(data_iter)), int(next(data_iter))) for _ in range(m)]
        ans = min_strokes_for_graph(n, edges)
        out.append(str(ans))

    print("\n".join(out))


if __name__ == "__main__":
    solve()
