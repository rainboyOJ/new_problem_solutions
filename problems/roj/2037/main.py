#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 04:30
# update_at: 2026-10-01 04:30

import sys
from heapq import heappop, heappush

NODE_COUNT = 52              # 牧场标记 a..z 与 A..Z 共 52 个，顶点编号取 0..51
COW_FIRST, BARN = 26, 51     # 有母牛的牧场 A..Y 编号 26..50；编号 51 的 'Z' 是谷仓
INF = 10**18


def node(name: bytes) -> int:
    """把牧场的单字母标记映射成顶点编号：a..z → 0..25，A..Z → 26..51。"""
    return name[0] - 97 if name[0] >= 97 else name[0] - 39  # 'a'=97→0，'A'=65→26


def dijkstra(adj: list[dict[int, int]], src: int) -> list[int]:
    """从 src 出发的单源最短路，返回 52 个牧场的距离（到不了为 INF）。"""
    dist = [INF] * NODE_COUNT
    dist[src] = 0
    heap = [(0, src)]
    while heap:
        d, u = heappop(heap)
        if d > dist[u]:  # 堆里的过期条目：此后又被更短的路取代过
            continue
        for v, w in adj[u].items():
            if d + w < dist[v]:
                dist[v] = d + w
                heappush(heap, (d + w, v))
    return dist


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    p = int(next(data))  # 题面的道路条数 P
    adj: list[dict[int, int]] = [dict() for _ in range(NODE_COUNT)]
    for _ in range(p):
        u, v = node(next(data)), node(next(data))  # 道路两端的牧场
        w = int(next(data))                        # 道路长度
        # 两个牧场间可能有多条路：只留最短的一条；正权自环不会改进 dist[u]
        adj[u][v] = min(adj[u].get(v, INF), w)
        adj[v][u] = min(adj[v].get(u, INF), w)

    dist = dijkstra(adj, BARN)  # 所有牛都走向谷仓，等价于从谷仓出发算单源最短路
    best = min(range(COW_FIRST, BARN), key=dist.__getitem__)  # 只在 A..Y 里挑最快的
    print(chr(best + 39), dist[best])  # 编号 26..50 还原成 'A'..'Y'


if __name__ == "__main__":
    solve()
