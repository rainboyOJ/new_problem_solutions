#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 14:44
# update_at: 2026-09-30 14:44

import heapq
import sys

INF = 10**18  # 未发现的长度哨兵：最长简单路远小于此


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    farm_cnt, road_cnt = next(data), next(data)

    road: list[list[tuple[int, int]]] = [[] for _ in range(farm_cnt + 1)]  # 2R 条有向邻接
    for _ in range(road_cnt):
        a, b, d = next(data), next(data), next(data)
        road[a].append((b, d))
        road[b].append((a, d))

    # 每个农场保留"最短 + 次短"两个长度；第二短路允许重复走边，所以松弛不禁止回头，
    # 只要求候选值严格落在 (最短, 次短) 开区间内才登记为新的次短。
    best = [[INF, INF] for _ in range(farm_cnt + 1)]
    best[1][0] = 0
    heap = [(0, 1)]  # (从农场 1 走到的长度, 农场编号)
    while heap:
        length, v = heapq.heappop(heap)
        if length > best[v][1]:  # 期间已登记更小的次短，堆里这条是过期项
            continue
        for nxt, w in road[v]:
            cand = length + w
            if cand < best[nxt][0]:  # 刷新最短：原最短自动降级为次短
                best[nxt][1] = best[nxt][0]
                best[nxt][0] = cand
                heapq.heappush(heap, (cand, nxt))
            elif best[nxt][0] < cand < best[nxt][1]:  # 严格更长但不超过现次短
                best[nxt][1] = cand
                heapq.heappush(heap, (cand, nxt))

    print(best[farm_cnt][1])


if __name__ == "__main__":
    solve()
