#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 14:15
# update_at: 2026-09-30 14:15

import sys

INF = 10**9  # 哨兵：v_i、p_ij 都不超过 1e5，INF 一定比任何真实边权大


def prim(edge: list[list[int]]) -> int:
    """稠密图最小生成树（Prim + 邻接矩阵）：返回所有点连通的最小总边权。"""
    n = len(edge)
    used = [False] * n
    best = [INF] * n  # 每个未选点连到已选点集的最便宜一条边
    best[0] = 0
    total = 0
    for _ in range(n):
        u = min((best[i], i) for i in range(n) if not used[i])[1]  # 取最便宜的未选点
        used[u] = True
        total += best[u]
        row = edge[u]
        # u 入选后，用 u 连出的边刷新其余未选点的最便宜入边
        for v in range(n):
            if not used[v] and row[v] < best[v]:
                best[v] = row[v]
    return total


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    v = [next(data) for _ in range(n)]                 # 各矿井建发电站的费用
    p = [[next(data) for _ in range(n)] for _ in range(n)]  # n×n 电网费用矩阵
    # 超级源点 n：与矿井 i 连一条权 v_i 的边，在 i 建电站 = 选中这条边
    edge = [row + [v[i]] for i, row in enumerate(p)] + [v + [0]]
    print(prim(edge))


if __name__ == "__main__":
    solve()
