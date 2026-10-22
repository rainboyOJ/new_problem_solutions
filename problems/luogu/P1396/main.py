#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-21 16:59
# update_at: 2026-10-21 17:30
#
# main.py：营救。求 s 到 t 的所有路径中「路径上最大边权」的最小值，即瓶颈路。
# 本文件用 Kruskal + 并查集：按边权升序加边，边 (u,v) 一旦让 s 与 t 首次连通，
# 这条边的权值就是答案。
#
# 为什么对：Kruskal 处理完所有权 <= L 的边后，并查集的连通块恰好等于
# 「只走权 <= L 的边时图的分量」。于是
#   s、t 在只走权 <= L 的边时连通  <=>  Kruskal 加完权 <= L 的边后 s、t 已同块
# 而答案正是让 s、t 连通的最小阈值 L，所以「首次连通时那条边的权」就是 L。
# 这条性质只依赖边权的处理顺序，与同权边谁先谁后无关，所以任意一棵 MST 都对。

import sys

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Edge = tuple[int, int, int]  # (起点 u, 终点 v, 拥挤度 w)


def find(parent: list[int], x: int) -> int:
    """找 x 所在集合的根，顺路把路径上的点挂到根上（迭代压缩，不受递归深度限制）。"""
    root = x
    while parent[root] != root:
        root = parent[root]
    while parent[x] != root:
        parent[x], x = root, parent[x]
    return root


def main() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    start_node, target_node = next(data), next(data)

    edges: list[Edge] = []
    for _ in range(m):
        u, v, w = next(data), next(data), next(data)
        edges.append((u, v, w))

    # s == t 时不用走任何路，拥挤度上界是 0，必须先特判：
    # 否则并查集一开始就「已连通」，会错误地输出第一条边的权值。
    if start_node == target_node:
        print(0)
        return

    parent = list(range(n + 1))  # parent[x]：x 的父节点，x 是根时等于 x

    # 边权小的先试；这就是 Kruskal 的顺序，也是「阈值从低到高放开边」的顺序
    for u, v, w in sorted(edges, key=lambda edge: edge[2]):
        # 只靠路径压缩：单次操作摊还 O(log n)，本题 n <= 1e4 已经足够，
        # 所以不再额外维护集合大小做按大小合并。
        parent[find(parent, u)] = find(parent, v)

        # 加入这条边后 s 与 t 首次连通，它的权就是最小瓶颈值
        if find(parent, start_node) == find(parent, target_node):
            print(w)
            return

    print(0)  # 题面保证 s 一定能到达 t，走不到这里


if __name__ == "__main__":
    main()
