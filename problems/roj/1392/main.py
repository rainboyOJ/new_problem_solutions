#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 19:59
# update_at: 2026-10-08 19:59

import sys

type EdgeList = list[tuple[int, int, int]]  # 边表，每项是 (边权 w, 端点 u, 端点 v)，已按 w 升序


def find_root(parent: list[int], x: int) -> int:
    """并查集找根，带路径压缩（迭代版，不依赖递归深度）。"""
    while parent[x] != x:
        parent[x] = parent[parent[x]]
        x = parent[x]
    return x


def min_bottleneck(edges: EdgeList, n: int) -> tuple[int, int]:
    """Kruskal 求最小生成树，返回 (选中的边数, 选中边的最大边权)。

    边表已按边权升序排好；MST 同时是最小瓶颈生成树，所以最后加入的那条边的
    边权就是「连通全图所需的最大边权」的最小值。
    """
    parent = list(range(n + 1))
    chosen = 0      # 已选边数，连通全图后恰好是 n-1
    bottleneck = 0  # 已选边中的最大边权
    for w, u, v in edges:
        root_u, root_v = find_root(parent, u), find_root(parent, v)
        if root_u == root_v:
            continue
        parent[root_u] = root_v
        chosen += 1
        bottleneck = w  # 边已升序，最后加入的边权就是生成树的最大边权
        if chosen == n - 1:
            break           # 已经连通，后面的边权只会更大
    return chosen, bottleneck


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    # 读入顺序是 (u, v, w)，重排成 (w, u, v) 后整体排序，直接得到按边权升序的边表
    edges: EdgeList = []
    for _ in range(m):
        u, v, w = next(data), next(data), next(data)
        edges.append((w, u, v))
    edges.sort()

    chosen, bottleneck = min_bottleneck(edges, n)
    print(chosen, bottleneck)


if __name__ == "__main__":
    solve()
