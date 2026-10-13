#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-13 17:08
# update_at: 2026-10-13 17:08
#
# Floyd 全源最短路（邻接矩阵）：dist[i][j] 为 i 到 j 的最短路，INF 表示不可达。
# 点编号 1..n，坐标存 1 下标，dist[i][i] = 0，边权是两点间的欧氏距离；
# 本题只问 s 到 t，求完全源后取 dist[s][t] 输出。
# C++ 的 1e100 与 long long 在 Python 里是任意精度 int / float，不会溢出。

import sys
from math import hypot

INF = float("inf")  # 哨兵：inf 加任何有限边权仍是 inf，不会造出假最短路

type Grid = list[list[float]]
type Seq = list[float]


def build_dist(n: int, xs: Seq, ys: Seq, edges: list[tuple[int, int]]) -> Grid:
    """建邻接矩阵：dist[i][i] = 0，连线两端存欧氏距离，其余为 INF。"""
    dist: Grid = [[0.0 if i == j else INF for j in range(n + 1)] for i in range(n + 1)]
    for u, v in edges:
        w = hypot(xs[u] - xs[v], ys[u] - ys[v])  # 连线长度 = 两点间直线距离
        dist[u][v] = w
        dist[v][u] = w  # 连线是无向边，两个方向都登记
    return dist


def floyd(n: int, dist: Grid) -> Grid:
    """原地松弛：把 dist[i][j] 变成 i 到 j 的最短路长度。"""
    for k in range(1, n + 1):  # 中转点 k 必须在最外层，顺序不能换
        row_k = dist[k]
        for i in range(1, n + 1):
            i_to_k = dist[i][k]
            if i_to_k == INF:
                continue  # i 到中转点不可达，松弛无意义
            row_i = dist[i]
            for j in range(1, n + 1):
                if row_k[j] == INF:
                    continue
                whole = i_to_k + row_k[j]
                if whole < row_i[j]:
                    row_i[j] = whole
    return dist


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n = int(next(data))
    xs: Seq = [0.0] * (n + 1)
    ys: Seq = [0.0] * (n + 1)
    for i in range(1, n + 1):  # 点的坐标，1 下标
        xs[i] = int(next(data))
        ys[i] = int(next(data))

    m = int(next(data))
    edges = [(int(next(data)), int(next(data))) for _ in range(m)]
    s, t = int(next(data)), int(next(data))

    dist = floyd(n, build_dist(n, xs, ys, edges))
    print(f"{dist[s][t]:.2f}")


if __name__ == "__main__":
    solve()
