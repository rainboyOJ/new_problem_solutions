#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 05:58
# update_at: 2026-10-01 06:04

import sys
from heapq import heappop, heappush
from collections.abc import Iterator

INF = 10**9  # 篱笆总长不超过 100*255，用它当"走不到"的哨兵

Junction = tuple[int, ...]  # 端点身份 = 在这个端点上相接的篱笆标号集合，同集合即同端点
Fence = tuple[Junction, Junction, int]  # (一端的端点, 另一端的端点, 长度)
Edge = tuple[Junction, int, int]  # (对端端点, 长度, 篱笆标号)


def detour(adj: dict[Junction, list[Edge]], start: Junction, goal: Junction, banned: int) -> int:
    """禁用 banned 号篱笆后，从 start 沿至少一条篱笆走到 goal 的最短长度，走不到返回 INF。

    出发点先迈一步再入堆，所以 start == goal（某段篱笆两端落在同一端点）时
    得到的是一条真正的回路，而不是长度为 0 的空路。
    """
    dist: dict[Junction, int] = {}
    pq: list[tuple[int, Junction]] = []
    for y, w, eid in adj[start]:
        if eid != banned and w < dist.get(y, INF):
            dist[y] = w
            heappush(pq, (w, y))
    while pq:
        d, x = heappop(pq)
        if d > dist[x]:  # 过期堆项
            continue
        if x == goal:
            return d
        for y, w, eid in adj[x]:
            if eid != banned and d + w < dist.get(y, INF):
                dist[y] = d + w
                heappush(pq, (d + w, y))
    return INF


def solve() -> None:
    data: Iterator[int] = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    fences: list[Fence] = []
    for _ in range(n):
        s, length, left_count, right_count = next(data), next(data), next(data), next(data)
        left = [next(data) for _ in range(left_count)]
        right = [next(data) for _ in range(right_count)]
        # 题面只给"相接关系"，不给坐标：把"该端点上所有篱笆的标号集合"直接当作端点编号
        fences.append((tuple(sorted(left + [s])), tuple(sorted(right + [s])), length))

    adj: dict[Junction, list[Edge]] = {}
    for eid, (u, v, length) in enumerate(fences):
        adj.setdefault(u, []).append((v, length, eid))
        adj.setdefault(v, []).append((u, length, eid))

    # 每条篱笆轮流充当回路的一环：禁掉它，两个端点之间的最短路就是回路剩下的部分
    print(min(length + detour(adj, u, v, eid) for eid, (u, v, length) in enumerate(fences)))


if __name__ == "__main__":
    solve()
