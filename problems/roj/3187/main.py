#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 00:10
# update_at: 2026-10-02 00:10

import sys
from array import array
from heapq import heappop, heappush
from math import prod

MOD = (1 << 31) - 1  # 答案要模的数 2^31 - 1
SHIFT = 10           # 打包用：低 10 位专放房间编号（N ≤ 1000 < 2^10），高位放边权
ID_MASK = (1 << SHIFT) - 1
INF = 1 << 60        # 不可达的距离哨兵，足够大，不会和真实距离混淆


def shortest_distances(n: int, adj: list[array]) -> list[int]:
    """求 1 号房间到每个房间的最短距离 D[]。

    堆里把 (距离, 编号) 打包成一个整数，低位留给编号，于是整数序就是距离序，
    省掉元组比较；距离相同也不会出错——编号只用来区分不同的房间。
    """
    dist = [INF] * n
    dist[0] = 0
    pq = [0]                                    # 源点：距离 0、编号 0
    while pq:
        item = heappop(pq)
        d, u = item >> SHIFT, item & ID_MASK
        if d > dist[u]:
            continue                            # 这项已被更短的距离取代
        for packed in adj[u]:
            v, nd = packed & ID_MASK, d + (packed >> SHIFT)
            if nd < dist[v]:                    # 必须处理「变小」分支，不能只处理首次到达
                dist[v] = nd
                heappush(pq, (nd << SHIFT) | v)
    return dist


def tight_edge_counts(n: int, edges: array, dist: list[int]) -> list[int]:
    """数每个房间有几条「紧边」：D[另一端] + w 恰好等于 D[自己]。

    同一条紧边只会算到它「距离更远」的那个端点上：边权为正，两个方向不可能同时成立。
    自环两端都是自己，D[x] + w 严格大于 D[x]，自然被排除。
    """
    tight = [0] * n
    for i in range(0, len(edges), 3):
        x, y, w = edges[i], edges[i + 1], edges[i + 2]
        if dist[x] + w == dist[y]:
            tight[y] += 1
        elif dist[y] + w == dist[x]:
            tight[x] += 1
    return tight


def solve() -> None:
    # 按空白分词而不是按行拆：题面保证的是空白分隔的数字，换行位置并不固定。
    # 生成器逐行惰性读取，不会把整份输入同时留在内存里。
    tokens = (int(t) for line in sys.stdin.buffer for t in line.split())
    n, m = next(tokens), next(tokens)

    # M 最大约 5×10^5，邻接表用 array('i') 装打包好的整数：每个邻居只占 4 字节，
    # 比 Python 列表省一个数量级的内存，遍历时也不必反复装箱。
    adj: list[array] = [array('i') for _ in range(n)]
    edges = array('i')                          # 原始边表，最后数紧边时还要再扫一遍
    for _ in range(m):
        x, y, w = next(tokens) - 1, next(tokens) - 1, next(tokens)
        edges.extend((x, y, w))
        adj[x].append((w << SHIFT) | y)         # 通道双向，两边都要挂
        adj[y].append((w << SHIFT) | x)

    # 每个房间 2..N 独立挑一条紧边当树边，方案数就是可选条数的乘积
    print(prod(tight_edge_counts(n, edges, shortest_distances(n, adj))[1:]) % MOD)


if __name__ == "__main__":
    solve()
