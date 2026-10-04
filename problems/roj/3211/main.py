#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 02:10
# update_at: 2026-10-02 02:10

import sys
from itertools import combinations

INF = 10**9  # 不连通哨兵；n <= 100，真实最短路长度最多 99


def all_pairs_shortest_paths(n: int, edges: list[tuple[int, int]]) -> list[list[int]]:
    """回答"任意两个环之间最少要经过几条绳索"：dist[u][v] 即两环距离，INF 表示不连通。"""
    # 环用 0 基编号；对角线为 0，其余先当作不连通
    dist = [[0 if i == j else INF for j in range(n)] for i in range(n)]
    for u, v in edges:
        dist[u][v] = dist[v][u] = 1  # 同一对环之间的重边只留一条，多出的绳永远拉不紧

    # Floyd：第 k 轮允许中转环 k，把整行松弛为"原值"与"先到 k 再走 k->j"的逐列较小者
    for k in range(n):
        row_k = dist[k]
        for i, row_i in enumerate(dist):
            reach = row_i[k]  # i 到中转环 k 的距离
            if reach < INF:
                dist[i] = [min(have, reach + via) for have, via in zip(row_i, row_k)]
    return dist


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    n, m = data[0], data[1]  # m 是题面声明的绳索数
    # 按实际读到最后的整数成对取边，而不是照 m 取 m 次：真实数据里 m 偶尔比给出的行数大
    edges = [(a - 1, b - 1) for a, b in zip(data[2::2], data[3::2])]  # 题面编号 1..n

    dist = all_pairs_shortest_paths(n, edges)

    # 拉紧 L 和 R 时，只有那条最短路径上的绳索会绷直，所以一条路径的长度就是能拉紧的绳索数；
    # 枚举所有环对取最大，不连通的环对一条也拉不紧。
    print(
        max(
            (dist[u][v] for u, v in combinations(range(n), 2) if dist[u][v] < INF),
            default=0,
        )
    )


if __name__ == "__main__":
    solve()
