#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 18:13
# update_at: 2026-10-07 18:13

import heapq
import sys
from collections.abc import Iterator

INF = 1 << 62  # 不可达哨兵：大于任何可能到达时刻（n · Σt_i ≤ 2e10）

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Routes = list[list[int]]             # 每条线路的站台序列，环长 = 周期 len(route)
type Stops = list[list[tuple[int, int]]]  # 站台 -> [(线路号, 该站台在线路中的位置)]


def read_input(data: Iterator[int]) -> tuple[int, Routes, Stops]:
    """读入 n、m 与 m 条线路，同时把每个 (线路号, 位置) 登记到它所在站台名下。"""
    n, m = next(data), next(data)
    routes: Routes = []
    stops: Stops = [[] for _ in range(n + 1)]
    for r in range(m):
        length = next(data)  # 题面的 t_i
        route = [next(data) for _ in range(length)]
        routes.append(route)
        for p, v in enumerate(route):
            stops[v].append((r, p))
    return n, routes, stops


def earliest_arrival(n: int, routes: Routes, stops: Stops) -> list[int]:
    """Dijkstra：dist[v] = 最早到达站台 v 的时刻，边权（等车 + 坐一站）松弛时实时算。"""
    dist = [INF] * (n + 1)
    dist[1] = 0
    done = [False] * (n + 1)
    heap = [(0, 1)]
    while heap:
        d, v = heapq.heappop(heap)
        if done[v]:
            continue
        done[v] = True
        for r, p in stops[v]:
            route = routes[r]
            period = len(route)
            # 车只在时刻 ≡ p (mod period) 停在 s_i[p]：等到相位 p 上车，1 个时刻后到下一站
            board = d + (p - d) % period
            nxt = route[(p + 1) % period]
            if board + 1 < dist[nxt]:
                dist[nxt] = board + 1
                heapq.heappush(heap, (board + 1, nxt))
    return dist


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, routes, stops = read_input(data)
    dist = earliest_arrival(n, routes, stops)
    print(' '.join('-1' if dist[v] >= INF else str(dist[v]) for v in range(2, n + 1)))


if __name__ == "__main__":
    solve()
