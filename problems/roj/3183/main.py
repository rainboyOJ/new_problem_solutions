#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 23:50
# update_at: 2026-10-01 23:50

import sys

INF = 1 << 60  # “不可达”哨兵；真实最短路不超过 100 × 499，远小于它


def restore(i: int, j: int, mid: list[list[int]]) -> list[int]:
    """还原最短路 i→j 依次经过的点（含两端）。

    mid[i][j] = 0 表示 i、j 直接相连，路径就是 [i, j]；
    否则这条最短路在 mid[i][j] 处拐弯，拼起来并去掉重复的拐点即可。
    """
    k = mid[i][j]
    return [i, j] if k == 0 else restore(i, k, mid) + restore(k, j, mid)[1:]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    edges = [(next(data), next(data), next(data)) for _ in range(m)]
    # 题面保证编号落在 1..N；这里仍按实际出现的最大编号开表，避免脏数据越界
    V = max([n, *(x for u, v, _ in edges for x in (u, v))])

    # w = 原始边权（重边只留最短的一条）；dist = 当前只允许经过中转点 1..k-1 的最短路
    w = [[INF] * (V + 1) for _ in range(V + 1)]
    for u, v, length in edges:
        if length < w[u][v]:  # 重边取最小，重复边的较大值不会出现在最优环里
            w[u][v] = w[v][u] = length
    for i in range(V + 1):
        w[i][i] = 0
    dist = [row[:] for row in w]
    mid = [[0] * (V + 1) for _ in range(V + 1)]  # mid[i][j]：i→j 最短路上的中转点

    best, loop = INF, []
    for k in range(1, n + 1):
        wk, dk = w[k], dist[k]

        # 阶段一：把 k 当作环上编号最大的点。此刻 dist 只借用了 1..k-1 中转，
        # 于是 dist[i][j] + w[i][k] + w[k][j] 恰好拼出一个经过 k 的简单环。
        for i in range(1, k):
            wik = wk[i]
            if wik >= INF:  # i、k 之间没有边，这个环不可能成立
                continue
            di = dist[i]
            for j in range(i + 1, k):
                cand = di[j] + wik + wk[j]
                if cand < best:
                    best, loop = cand, restore(i, j, mid) + [k]  # i..j 段接上 k

        # 阶段二：k 升级为中转点，用它松弛出新的最短路
        for i in range(1, V + 1):
            dik = dist[i][k]
            if dik >= INF:
                continue
            di = dist[i]
            for j in range(1, V + 1):
                nxt = dik + dk[j]
                if nxt < di[j]:
                    di[j], mid[i][j] = nxt, k

    print(' '.join(map(str, loop)) if loop else 'No solution.')


if __name__ == "__main__":
    solve()
