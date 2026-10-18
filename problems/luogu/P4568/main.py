#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-17 01:42
# update_at: 2026-10-18 20:26
#
# main.py：不显式建分层图，把「用了几次免费机会」当成 distance 的第一维，
# 在 Dijkstra 的松弛里同时做两种转移（付费留在本层 / 免费降到下一层）。

import sys
from heapq import heappop, heappush

type WeightedAdj = list[list[tuple[int, int]]]  # graph[city]：若干 (邻城, 花费)

INF = 1 << 60


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    city_count, edge_count, free_limit = next(data), next(data), next(data)
    start, target = next(data), next(data)

    graph: WeightedAdj = [[] for _ in range(city_count)]
    for _ in range(edge_count):
        u, v, cost = next(data), next(data), next(data)
        graph[u].append((v, cost))
        graph[v].append((u, cost))

    # distance[used][city]：到达 city、恰好使用 used 次免费机会的最小花费
    distance = [[INF] * city_count for _ in range(free_limit + 1)]
    distance[0][start] = 0                  # 起点一次免费机会都还没用
    heap: list[tuple[int, int, int]] = [(0, start, 0)]  # (花费, 城市, 已用次数)

    while heap:
        current, city, used = heappop(heap)
        if current != distance[used][city]:
            continue                        # 堆里的过期条目
        for neighbor, cost in graph[city]:
            # 转移一：这次不免费，付费留在本层。
            paid = current + cost
            if paid < distance[used][neighbor]:
                distance[used][neighbor] = paid
                heappush(heap, (paid, neighbor, used))
            # 转移二：这次免费用掉一张券，代价不变但层数加一。
            if used < free_limit and current < distance[used + 1][neighbor]:
                distance[used + 1][neighbor] = current
                heappush(heap, (current, neighbor, used + 1))

    # 题目是「最多 k 次」：只取 distance[k][target] 会错，
    # 最优路径可能只用了不到 k 次机会，甚至第 k 层根本不可达。
    print(min(layer[target] for layer in distance))


if __name__ == "__main__":
    solve()
