#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 00:10
# update_at: 2026-10-02 00:10

import sys
from operator import add

INF = float("inf")  # 还走不到的距离哨兵：inf + inf = inf，min 时自然被淘汰

Matrix = list[list[float]]


def min_plus_mul(a: Matrix, b: Matrix) -> Matrix:
    """min-plus 乘法：c[i][j] = min_k(a[i][k] + b[k][j])，含义是“接上两段路程”。"""
    b_t = list(zip(*b))  # 转置成按行取列，让内层 min(map(add, ...)) 跑在 C 级速度
    return [[min(map(add, row, col)) for col in b_t] for row in a]


def min_plus_power(adj: Matrix, n: int) -> Matrix:
    """min-plus 快速幂：返回 dist[i][j] = 从 i 恰好走 n 条边到 j 的最短距离。"""
    size = len(adj)
    result: Matrix = [[INF] * size for _ in range(size)]
    for i in range(size):
        result[i][i] = 0  # 恰走 0 条边：只有自己到自己，是乘法的单位元
    base = adj
    while n:
        if n & 1:
            result = min_plus_mul(result, base)
        n >>= 1
        if n:  # 最后一次乘方前不再平方，省一次 O(V^3)
            base = min_plus_mul(base, base)
    return result


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)       # 恰好经过的边数
    t = next(data)       # 无向边条数
    s = next(data)       # 起点
    e = next(data)       # 终点

    triples: list[tuple[int, int, int]] = []
    ids: dict[int, int] = {}  # 点编号离散化：真正出现过的点最多 2*t 个
    for _ in range(t):
        length = next(data)
        u, v = next(data), next(data)
        triples.append((length, u, v))
        ids.setdefault(u, len(ids))
        ids.setdefault(v, len(ids))

    # 邻接矩阵：同一对点可能有多条边，只保留最短的那条
    adj: Matrix = [[INF] * len(ids) for _ in range(len(ids))]
    for length, u, v in triples:
        iu, iv = ids[u], ids[v]
        adj[iu][iv] = adj[iv][iu] = min(adj[iu][iv], length)

    dist = min_plus_power(adj, n)
    print(int(dist[ids[s]][ids[e]]))


if __name__ == "__main__":
    solve()
