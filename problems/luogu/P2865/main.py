#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-17 01:40
# update_at: 2026-10-20 17:50
#
# main.py：次短路。求 1 到 n 严格大于最短路的路径长度中的最小值。
# 题面允许路径共用道路、允许回头，所以次短路可能不是简单路径，
# 例如链 1-2-3（边权皆 1）的次短路是 1-2-1-2-3 = 4。
# 因此把每个点的状态从一个距离扩成两个严格不同的距离：
#   shortest[v] 到 v 的最小值；second[v] 严格大于 shortest[v] 的最小值。
# 用堆按长度升序弹出候选，每条候选都是一条真实路径。
# 一个点的最短路被推翻时，旧值不能丢——它仍是真实路径，应降级为次短候选，
# 这就是下面那个多重赋值交换的意义，去掉它结果会错。
# 这里不需要 visited：状态扩成两个后一个点要被处理两次，定型判断从"按点"
# 变成"按记录"，用 current > second[node] 筛掉过期记录即可。

import sys
from heapq import heappop, heappush

INF = 10**30  # 整数哨兵，比任何合法路径都大；Python int 任意精度，不会溢出


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, r = next(data), next(data)

    graph: list[list[tuple[int, int]]] = [[] for _ in range(n + 1)]
    for _ in range(r):
        u, v, weight = next(data), next(data), next(data)
        graph[u].append((v, weight))
        graph[v].append((u, weight))  # 道路双向

    shortest = [INF] * (n + 1)  # 到 i 的最短距离
    second = [INF] * (n + 1)    # 到 i 的次短距离，要求严格大于 shortest[i]
    shortest[1] = 0
    heap: list[tuple[int, int]] = [(0, 1)]  # (距离, 点编号)，距离在前才能按它比大小

    while heap:
        current, node = heappop(heap)

        # 这条记录既不是最短路也不是次短路，已被更优的值取代，展开它无益
        if current > second[node]:
            continue

        for neighbor, weight in graph[node]:
            candidate = current + weight

            if candidate < shortest[neighbor]:
                # 找到更短的最短路：旧值是真实路径不能丢，
                # 交换后 candidate 变成旧的最短路，正好进入下面去竞争次短
                candidate, shortest[neighbor] = shortest[neighbor], candidate
                heappush(heap, (shortest[neighbor], neighbor))

            # 只接受严格大于最短路、且能改善次短的候选；
            # 长度等于最短路的另一条路径不算次短路，所以这里是 < 而非 <=
            if shortest[neighbor] < candidate < second[neighbor]:
                second[neighbor] = candidate
                heappush(heap, (candidate, neighbor))

    print(second[n])


if __name__ == "__main__":
    solve()
