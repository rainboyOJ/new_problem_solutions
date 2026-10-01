#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 00:36
# update_at: 2026-10-02 00:36

import sys
from collections import deque


def has_neg_cycle(n: int, graph: list[list[tuple[int, int]]]) -> bool:
    """图（边权为 mid*t - f）中是否存在负环（SPFA 判负环）。"""
    cnt = [0] * (n + 1)               # cnt[v] = 点 v 被松弛的次数
    in_queue = [False] * (n + 1)
    dis = [0.0] * (n + 1)             # 超级源点连向所有点，dis 初始全 0
    queue = deque(range(1, n + 1))    # 超级源点入队等价于所有点初始就在队列里
    in_queue[1:] = [True] * n

    while queue:
        u = queue.popleft()
        in_queue[u] = False
        for v, w in graph[u]:
            nd = dis[u] + w
            if nd < dis[v]:
                dis[v] = nd
                cnt[v] += 1
                if cnt[v] >= n:       # 一个点被松弛 n 次 ⇒ 经过它存在负环
                    return True
                if not in_queue[v]:
                    in_queue[v] = True
                    queue.append(v)
    return False


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    L = next(data)  # 点数
    P = next(data)  # 边数

    fun = [0] + [next(data) for _ in range(L)]  # 点权：fun[i] = 景点的乐趣值

    # 邻接表：u -> [(v, time), ...]
    graph: list[list[tuple[int, int]]] = [[] for _ in range(L + 1)]
    for _ in range(P):
        a, b, t = next(data), next(data), next(data)
        graph[a].append((b, t))

    # 01分数规划：二分比值 mid，判是否存在环满足 Σ(mid*t - f) < 0，即环的 Σf/Σt > mid
    lo, hi = 0.0, 1000.0  # f,t 均 <= 1000，比值不超过 1000
    for _ in range(30):   # 30 次二分后区间长 < 1e-6，足够保留两位小数
        mid = (lo + hi) / 2
        # 点权 f 记在边的终点上：环的边权和 = mid·Σt - Σf(环上点)
        graph_adj = [[(v, mid * t - fun[v]) for v, t in adj] for u, adj in enumerate(graph)]
        if has_neg_cycle(L, graph_adj):  # 有负环 ⇒ 存在环的比值 > mid
            lo = mid   # 答案比 mid 大，抬高下界
        else:
            hi = mid   # 所有环的比值 <= mid，压低上界

    print(f'{hi:.2f}')  # 二分收敛到最大比值


if __name__ == "__main__":
    solve()
