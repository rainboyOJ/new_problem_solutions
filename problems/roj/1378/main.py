#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 16:42
# update_at: 2026-10-08 16:42

import sys

INF = 10**18  # 无穷大：足够大，且与边权相加不会溢出

type Matrix = list[list[int | None]]  # 邻接矩阵，None 表示无边


def read_matrix(n: int, rows: list[str]) -> Matrix:
    """按行读入邻接矩阵：'-' 记为 None（无边），对角线上的 0 保留但自环不影响最短路。

    必须按行读、不能把整个文件 split() 成 token 连读：数据文件 SHOPTH8.IN 的
    第 10 行只有 19 个 token（n=20），连读会让后面所有行整体错位；按行读时
    短行只影响自己这一行，不足的列按无边处理。
    """
    adj: Matrix = [[None] * (n + 1) for _ in range(n + 1)]
    for i, row in enumerate(rows[:n], 1):
        for j, token in enumerate(row.split(), 1):
            if j > n:                      # 行内 token 多于 n 个（脏行）时只取前 n 个
                break
            if token != '-':
                adj[i][j] = int(token)
    return adj


def shortest(n: int, source: int, adj: Matrix) -> list[int]:
    """Bellman-Ford：无负环时松弛 n-1 轮足够，返回 dist[1..n]。

    有负边所以不能用 Dijkstra；题面保证所有有向环权值和为正，即无负环。
    """
    dist = [INF] * (n + 1)
    dist[source] = 0
    for _ in range(n - 1):
        changed = False                    # 本轮没有变短就已收敛，提前退出
        for i in range(1, n + 1):
            if dist[i] == INF:
                continue
            for j in range(1, n + 1):
                w = adj[i][j]
                if w is None:
                    continue
                cand = dist[i] + w         # 用 i 中转一次的距离
                if cand < dist[j]:
                    dist[j] = cand
                    changed = True
        if not changed:
            break
    return dist


def solve() -> None:
    data = iter(sys.stdin.read().splitlines())
    n = int(next(data))                    # 顶点数
    source = int(next(data))               # 源点
    rows = [next(data) for _ in range(n)]
    dist = shortest(n, source, read_matrix(n, rows))
    print('\n'.join(f"({source} -> {i}) = {dist[i]}"
                    for i in range(1, n + 1) if i != source))


if __name__ == "__main__":
    solve()
