#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 06:09
# update_at: 2026-09-30 06:09

import sys
from math import dist, inf


def solve() -> None:
    tokens = iter(sys.stdin.buffer.read().split())
    n = int(next(tokens))
    points = [(float(next(tokens)), float(next(tokens))) for _ in range(n)]
    # 邻接矩阵的每一行是一个长度为 n 的 01 串，逐位取出。
    edge = [
        [float(row[j : j + 1]) for j in range(n)]
        for row in (next(tokens) for _ in range(n))
    ]

    # 边权参与加法，所以这里必须用真实距离：先开好方，Floyd 只做加减比较。
    span: list[list[float]] = [[inf] * n for _ in range(n)]
    for k, row in enumerate(edge):
        span[k][k] = 0.0
        for i, flag in enumerate(row):
            if flag and i != k:                       # 只有真的连了边才需要算距离
                span[k][i] = dist(points[k], points[i])

    for k in range(n):                                # Floyd：第 k 轮只用第 k 列当跳板
        col = [row[k] for row in span]                # 本轮内该列不会被改写，先取出来
        for i in range(n):
            begin = col[i]
            if begin < inf:                           # inf 表示 i 到 k 不连通，整行不用扫
                span[i] = [x if x <= begin + y else begin + y for x, y in zip(span[i], col)]

    far = [max(value for value in row if value < inf) for row in span]  # 每个点到本牧场最远点的距离
    diameter = max(far)                               # 只加一条边，原直径消不掉，是答案的下界
    bridge = min(                                     # 枚举连接两个不同牧场的边 (i, j)
        far[i] + dist(points[i], points[j]) + far[j]
        for i in range(n)
        for j in range(n)
        if span[i][j] == inf                          # inf 恰好表示 i、j 不在同一个牧场
    )
    print(f"{max(diameter, bridge):.6f}")


if __name__ == "__main__":
    solve()
