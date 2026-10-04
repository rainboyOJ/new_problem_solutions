#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 04:43
# update_at: 2026-10-02 04:43

import sys
from collections.abc import Iterable
from heapq import heappop, heappush
from math import hypot


def rect_fourth(pts: list[tuple[int, int]]) -> tuple[int, int]:
    """矩形三个顶点补出第四个顶点。

    三个已知点里恰有一个顶点的两条邻边都在已知点中（直角顶点），记它为 c、
    另两点为 a、b，则第四个顶点 = a + b - c（对角线互相平分）。
    """
    for i, (cx, cy) in enumerate(pts):
        (ax, ay), (bx, by) = [p for j, p in enumerate(pts) if j != i]
        if (ax - cx) * (bx - cx) + (ay - cy) * (by - cy) == 0:  # a、b 在 c 处张成直角
            return ax + bx - cx, ay + by - cy
    raise ValueError("三个点构不成矩形顶点")  # 题面保证不会走到这里


def build_graph(
    airports: list[tuple[int, int]],
    rail: list[int],
    fly_price: int,
) -> list[list[tuple[int, float]]]:
    """把每个机场建成图上的一个点：同城机场两两修铁路，异城机场两两修航线。"""
    city_count = len(rail)
    adj: list[list[tuple[int, float]]] = [[] for _ in range(city_count * 4)]
    for c in range(city_count):
        base = c * 4
        for i in range(4):  # 同城 6 条铁路，单价 Ti
            xi, yi = airports[base + i]
            for j in range(i + 1, 4):
                xj, yj = airports[base + j]
                rail_cost = hypot(xi - xj, yi - yj) * rail[c]
                adj[base + i].append((base + j, rail_cost))
                adj[base + j].append((base + i, rail_cost))
        for c2 in range(c + 1, city_count):  # 异城 4x4=16 条航线，单价 t
            base2 = c2 * 4
            for i in range(4):
                xi, yi = airports[base + i]
                for j in range(4):
                    xj, yj = airports[base2 + j]
                    fly_cost = hypot(xi - xj, yi - yj) * fly_price
                    adj[base + i].append((base2 + j, fly_cost))
                    adj[base2 + j].append((base + i, fly_cost))
    return adj


def min_fare(adj: list[list[tuple[int, float]]], sources: Iterable[int], targets: set[int]) -> float:
    """多源 Dijkstra：从任一 source 出发、到任一 target 的最少花费，首次弹出 target 即答案。"""
    dist = [float("inf")] * len(adj)
    heap: list[tuple[float, int]] = []
    for s in sources:
        dist[s] = 0.0
        heappush(heap, (0.0, s))
    while heap:
        cost, u = heappop(heap)
        if cost > dist[u]:  # 过期堆元素
            continue
        if u in targets:  # 第一个弹出的目标点已被最短路覆盖
            return cost
        for v, w in adj[u]:
            if cost + w < dist[v]:
                dist[v] = cost + w
                heappush(heap, (cost + w, v))
    return float("inf")  # 航线全连通，实际不可达


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    cases = next(data)

    for _ in range(cases):
        city_count, fly_price = next(data), next(data)
        start, end = next(data), next(data)  # 出发城市 A、到达城市 B 的序号

        airports: list[tuple[int, int]] = []
        rail: list[int] = []  # 每城铁路单价 Ti，与 airports 按 4 个一组对齐
        for _ in range(city_count):
            pts = [(next(data), next(data)) for _ in range(3)]
            rail.append(next(data))  # 题面每行末尾的 Ti：该城铁路单位里程价格
            airports += [*pts, rect_fourth(pts)]

        adj = build_graph(airports, rail, fly_price)
        base_a, base_b = (start - 1) * 4, (end - 1) * 4
        # 出发、到达机场都可以任选：4 个起点并入、4 个终点任一到达即停
        fare = min_fare(
            adj,
            range(base_a, base_a + 4),
            set(range(base_b, base_b + 4)),
        )
        out.append(f"{fare:.1f}")

    print("\n".join(out))


if __name__ == "__main__":
    solve()
