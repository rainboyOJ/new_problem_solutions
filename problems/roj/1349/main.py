#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 06:34
# update_at: 2026-09-30 06:46

import sys

INF = 10**18  # dist 的初值：大于任何合法费用之和，表示暂时没有可用的接入边


def prim(cost: list[list[int]]) -> int:
    """返回费用矩阵所刻画完全图的最小生成树权值和，每轮接入最便宜的可接入点。"""
    n = len(cost)
    dist = [INF] * n        # dist[v] = 已接入点集连到 v 的最便宜一条边的费用
    dist[0] = 0             # 任选顶点 0 当根，接入自己不要钱
    unvisited = set(range(n))
    total = 0

    while unvisited:
        u = min(unvisited, key=dist.__getitem__)  # 最便宜的可接入点：连上它的那条边必须进生成树
        unvisited.remove(u)
        total += dist[u]
        for v in unvisited:  # 接入 u 后，各未接入点的最便宜接入边可能改成走 u
            dist[v] = min(dist[v], cost[u][v])  # 只遍历未接入点，否则 cost[u][u] 的 0 会覆写 dist[u]

    return total


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    n = data[0]             # 题面的计算机台数
    cost = [data[1 + i * n: 1 + (i + 1) * n] for i in range(n)]  # 第 i 行是顶点 i 到各点的费用
    print(prim(cost))


if __name__ == "__main__":
    solve()
