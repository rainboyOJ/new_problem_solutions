#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-13 17:08
# update_at: 2026-10-13 17:08
#
# 邻接表 + SPFA 单源最短路：本题只问 s 到 t 一条距离，没必要做全源。
# 点编号 1..n，g[u] 存 u 的出边 (终点 v, 边权 w)，无向边两个方向各 append 一次；
# 边权是两点间欧氏距离，恒为正，所以不存在负环，不用判负环。
# C++ 的 long long 与 1e100 在这里是 Python int / float，任意精度，不会溢出。

import sys
from collections import deque
from math import hypot

INF = float("inf")  # 不可达哨兵

type WeightedAdj = list[list[tuple[int, float]]]
type Seq = list[float]


def spfa(n: int, g: WeightedAdj, source: int, target: int) -> float:
    """返回 source 到 target 的最短路；不可达返回 INF。"""
    dist: Seq = [INF] * (n + 1)
    in_queue = [False] * (n + 1)  # 标记点是否已在队列里，避免重复入队
    dist[source] = 0

    q: deque[int] = deque([source])
    in_queue[source] = True
    while q:
        u = q.popleft()
        in_queue[u] = False  # 出队后允许再次入队（之后可能被松弛得更小）

        for v, w in g[u]:
            whole = dist[u] + w
            if whole < dist[v]:  # 只有被松弛过的点才可能继续松弛别人
                dist[v] = whole
                if not in_queue[v]:
                    q.append(v)
                    in_queue[v] = True

    return dist[target]


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n = int(next(data))
    xs: Seq = [0.0] * (n + 1)
    ys: Seq = [0.0] * (n + 1)
    for i in range(1, n + 1):  # 点的坐标，1 下标
        xs[i] = int(next(data))
        ys[i] = int(next(data))

    m = int(next(data))
    g: WeightedAdj = [[] for _ in range(n + 1)]
    for _ in range(m):
        u, v = int(next(data)), int(next(data))
        w = hypot(xs[u] - xs[v], ys[u] - ys[v])  # 连线长度 = 两点间直线距离
        g[u].append((v, w))
        g[v].append((u, w))  # 无向边：两个方向各存一次
    s, t = int(next(data)), int(next(data))

    print(f"{spfa(n, g, s, t):.2f}")


if __name__ == "__main__":
    solve()
