#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 14:30
# update_at: 2026-09-30 14:30

import sys

INF = 10 ** 12  # 无穷哨兵：环长是边权之和，不可能达到这个量级


def min_cycle(w: list[list[int]]) -> list[int]:
    """Floyd 最小环：以 k 为环上编号最大的点，用只经过编号 <k 的最短路 i→j 闭合成环。

    走到第 k 轮时 dist[i][j] 只经过 0..k-1，因此 i→j 的路径不含 k；再接上边
    (i,k)、(k,j) 就得到一个简单环。任一环都有唯一最大编号点，必在它那一轮被枚举到。
    返回环上依次的 1 编号节点；无环返回空表。
    """
    n = len(w)
    dist = [row[:] for row in w]  # dist[i][j]：中间点限制在 0..k-1 的最短路
    # 后继表：i 出发走向 j 的下一个点，用于把最短路还原成点序列
    nxt = [[j if w[i][j] < INF else -1 for j in range(n)] for i in range(n)]
    best = INF
    cycle: list[int] = []

    for k in range(n):
        # 第一步：先用「还没并入 k」的最短路找环，环 = i→…→j→k→i
        for i in range(k):
            if w[i][k] >= INF:
                continue  # i、k 不相邻，i→j→k 闭不回环
            for j in range(i + 1, k):
                # 边 (k,j) 不存在时 w[k][j]=INF，环长溢出到哨兵以上，自然不会更优
                cand = dist[i][j] + w[i][k] + w[k][j]
                if cand < best:
                    best = cand
                    path = [i]
                    while path[-1] != j:  # 沿后继表回溯 i→…→j
                        path.append(nxt[path[-1]][j])
                    cycle = path + [k]  # 按环上顺序：i→…→j→k，再回到 i

        # 第二步：把 k 并入最短路，供后续轮次使用
        for i in range(n):
            via_k = dist[i][k]
            if via_k >= INF:
                continue
            for j in range(n):
                if via_k + dist[k][j] < dist[i][j]:
                    dist[i][j] = via_k + dist[k][j]
                    nxt[i][j] = nxt[i][k]  # i 去 j 先迈向 i 的 k-后继

    return [x + 1 for x in cycle]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    # 邻接矩阵存边权：重边取最短（环上换用更短的平行边只会更优），自环凑不出 3 点环，忽略
    w = [[INF] * n for _ in range(n)]
    for i in range(n):
        w[i][i] = 0
    for _ in range(m):
        x, y, z = next(data) - 1, next(data) - 1, next(data)
        if x != y and z < w[x][y]:
            w[x][y] = w[y][x] = z

    cycle = min_cycle(w)
    print(' '.join(map(str, cycle)) if cycle else 'No solution.')


if __name__ == "__main__":
    solve()
