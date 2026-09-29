#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 06:18
# update_at: 2026-09-30 06:13

import sys
from math import dist as segment  # 两点间直线距离，就是一条连线的边权
from math import inf as INF  # 不可达哨兵：INF 加任何有限数仍是 INF，不会造出假最短路


def all_pairs_shortest(n: int, graph: list[list[float]]) -> list[list[float]]:
    """原地松弛邻接矩阵，使 graph[i][j] 成为 i 到 j 的最短路径长度（Floyd）。"""
    for k in range(n):
        row_k = graph[k]  # 作为中转点的第 k 行
        for row in graph:  # 逐个起点 i 松弛
            i_to_k = row[k]  # 松弛前的 i → k 距离，行内共享，提到内层循环外
            for j in range(n):  # 用 k 中转：min(i → j, i → k → j)
                through_k = i_to_k + row_k[j]
                if through_k < row[j]:
                    row[j] = through_k
    return graph


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n = int(next(data))
    points = [(int(next(data)), int(next(data))) for _ in range(n)]

    # 邻接矩阵：同一点到自己是 0，其余先记为不可达；每条连线登记两个方向
    graph = [[0.0 if i == j else INF for j in range(n)] for i in range(n)]
    m = int(next(data))
    for _ in range(m):
        u, v = int(next(data)) - 1, int(next(data)) - 1
        graph[u][v] = graph[v][u] = segment(points[u], points[v])  # u == v 时写入 0，不改变矩阵

    all_pairs_shortest(n, graph)
    s, t = int(next(data)) - 1, int(next(data)) - 1
    print(f"{graph[s][t]:.2f}")


if __name__ == "__main__":
    solve()
