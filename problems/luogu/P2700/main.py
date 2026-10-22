#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-21 21:40
# update_at: 2026-10-21 21:40
#
# P2700 逐个击破
# 正难则反：不直接想「删哪些边」，而是想「尽量多保留边」，答案 = 总边权 - 最大保留边权。
# 保留的边构成森林，要求每个连通块里至多有一个敌城。
# 按边权从大到小扫：这条边若把两个「都含敌城」的块连起来，就必须破坏（付代价）；
# 否则保留它、合并两块。这和最小生成树的 Kruskal 是同一套并查集框架。

import sys

type Edge = tuple[int, int, int]  # (一端 u, 另一端 v, 破坏代价 w)


def find(parent: list[int], x: int) -> int:
    """找 x 所在集合的根，顺路把路径上的点挂到根上（迭代压缩，不受递归深度限制）。"""
    root = x
    while parent[root] != root:
        root = parent[root]
    while parent[x] != root:
        parent[x], x = root, parent[x]
    return root


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, k = next(data), next(data)

    has_enemy = [False] * n  # has_enemy[根]：这个连通块里有没有被敌军占领的城市
    for _ in range(k):
        has_enemy[next(data)] = True  # 城市编号从 0 开始

    edges: list[Edge] = [(next(data), next(data), next(data)) for _ in range(n - 1)]

    parent = list(range(n))  # parent[x]：x 的父节点，x 是根时等于 x
    size = [1] * n           # size[x]：x 是根时这个连通块的城市数

    answer = 0
    for u, v, w in sorted(edges, key=lambda edge: edge[2], reverse=True):  # 代价大的先决定
        root_u, root_v = find(parent, u), find(parent, v)
        if has_enemy[root_u] and has_enemy[root_v]:
            answer += w  # 保留它会把两队敌军连起来，只能破坏
            continue
        if size[root_u] < size[root_v]:  # 小集合并到大集合下面
            root_u, root_v = root_v, root_u
        parent[root_v] = root_u
        size[root_u] += size[root_v]
        has_enemy[root_u] = has_enemy[root_u] or has_enemy[root_v]

    print(answer)


if __name__ == "__main__":
    solve()
