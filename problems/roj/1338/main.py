#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 05:57
# update_at: 2026-09-30 05:57

import sys

INF = 10 ** 9  # 距离上界：n <= 100、边权为 1，任何真实距离都远小于它


def all_pairs_dist(n: int, edges: list[tuple[int, int]]) -> list[list[int]]:
    """无向无权图的 Floyd：dist[u][v] 是 u 到 v 的最少边数。

    邻接矩阵初值：自己到自己是 0，有边是 1，其余是 INF；只用树的 n-1 条边松弛，
    不建邻接表是因为 Floyd 本来就按矩阵工作，规模只有 100 x 100。
    """
    dist = [[0 if i == j else INF for j in range(n)] for i in range(n)]
    for u, v in edges:
        if v:
            dist[u - 1][v - 1] = dist[v - 1][u - 1] = 1
    for k in range(n):
        dist_k = dist[k]                                     # 缓存第 k 行，省掉内层重复索引
        for dist_i in dist:
            d_ik = dist_i[k]
            for j in range(n):
                if dist_i[j] > d_ik + dist_k[j]:
                    dist_i[j] = d_ik + dist_k[j]
    return dist


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    # 每个结点的 (人口, 左孩子, 右孩子)：0 表示没有这个孩子
    nodes = [(next(data), next(data), next(data)) for _ in range(n)]
    population = [p for p, _, _ in nodes]

    # 医院可以建在任意结点上，所以先算两两之间的边数，再逐行求“人口 × 距离”
    edges = [(node, child) for node, (_, left, right) in enumerate(nodes, 1) for child in (left, right)]
    dist = all_pairs_dist(n, edges)
    # 每个候选位置各求一次总路程，取最小值就是答案
    print(min(sum(w * d for w, d in zip(population, row)) for row in dist))


if __name__ == "__main__":
    solve()
