#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 04:30
# update_at: 2026-10-01 04:33

import sys
from math import dist

INF = float("inf")  # 同一牧场内没有边直接相连的点对，Floyd 开始前的距离哨兵


def floyd(d: list[list[float]], n: int) -> None:
    """在原地把每个连通块内部的最短路算全（块间距离保持 INF）。"""
    for k in range(n):
        dk = d[k]
        for i in range(n):
            di = d[i]
            dik = di[k]
            if dik == INF:  # i 与 k 不同块，k 作中转点帮不到 i
                continue
            for j in range(n):
                via_k = dik + dk[j]
                if via_k < di[j]:
                    di[j] = via_k


def components(adj: list[list[int]], n: int) -> list[int]:
    """给每个牧区染上所在牧场的编号（取块内最小点标号）。"""
    comp = [-1] * n
    for s in range(n):
        if comp[s] != -1:
            continue
        cid = comp[s] = s
        stack = [s]
        while stack:
            for v, ok in enumerate(adj[stack.pop()]):
                if ok and comp[v] == -1:
                    comp[v] = cid
                    stack.append(v)
    return comp


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n = int(next(data))
    pt = [(int(next(data)), int(next(data))) for _ in range(n)]  # 每个牧区的坐标
    # 数据里矩阵行可能带 \r 或行内空格，先全部拼成 0/1 串再按行切块
    cells = b"".join(data).decode()
    adj = [[int(cells[i * n + j]) for j in range(n)] for i in range(n)]  # 邻接矩阵

    # 有边 → 欧几里得边权，无边 → INF，对角线为 0
    d = [[0.0 if i == j else (dist(pt[i], pt[j]) if adj[i][j] else INF)
          for j in range(n)] for i in range(n)]
    floyd(d, n)

    ecc = [max(w for w in d[i] if w != INF) for i in range(n)]  # 每点到本块内最远点的距离

    comp = components(adj, n)  # comp[i] = 牧场编号
    dia = [max(ecc[i] for i in range(n) if comp[i] == c) for c in set(comp)]  # 每个牧场的直径

    # 新直径 = 前半段最长路 + 新边 + 后半段最长路；新边权是两点间的欧几里得距离
    ans = min(ecc[i] + ecc[j] + dist(pt[i], pt[j])
              for i in range(n) for j in range(n) if comp[i] != comp[j])
    # 连新边不会把某个牧场自身"压细"，答案不低于原牧场直径的较大者
    print(f"{max(ans, max(dia)):.6f}")


if __name__ == "__main__":
    solve()
