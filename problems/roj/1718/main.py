#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 18:04
# update_at: 2026-10-07 18:04

import sys
from heapq import heappop, heappush

INF = 4 * 10**18  # 不可达哨兵：远大于任何真实最短路长度（上界约 2.5*10^13）

type Graph = list[list[tuple[int, int]]]        # 邻接表：g[u] 里是 (邻居, 边权)
type Dists = tuple[list[int], list[int], list[int], list[int]]  # 四条最短路 dA/dB/dC/dD


def dijkstra(src: int, g: Graph, n: int) -> list[int]:
    """src 到各点的最短路长度，不可达为 INF；g 传反图时求的就是"到 src 的最短路"。"""
    dist = [INF] * (n + 1)
    dist[src] = 0
    pq = [(0, src)]
    while pq:
        du, u = heappop(pq)
        if du > dist[u]:
            continue                       # 过期堆元素
        for v, w in g[u]:
            nd = du + w
            if nd < dist[v]:
                dist[v] = nd
                heappush(pq, (nd, v))
    return dist


def max_rewards(g: Graph, dists: Dists, targets: tuple[int, int]) -> int:
    """最大奖励数：公共最短路 DAG 上的最长节点链；有一人到不了终点时返回 -1。

    边 (u,v,w) 能接链当且仅当它同时落在 A→B 与 C→D 的某条最短路上；
    沿这样的边 dA 严格增大，按 dA 排序遍历即拓扑序，一次线性 DP 收尾。
    """
    dA, dB, dC, dD = dists
    dab, dcd = targets                      # 两条最短路各自的长度
    if dab >= INF or dcd >= INF:            # 小 P 走不到 B 或小 R 走不到 D
        return -1

    shared = [v for v in range(1, len(dA)) if dA[v] + dB[v] == dab and dC[v] + dD[v] == dcd]
    dp = dict.fromkeys(shared, 1)           # 每个公共点本身就能换一次奖励
    for u in sorted(shared, key=dA.__getitem__):
        for v, w in g[u]:
            if dA[u] + w + dB[v] == dab and dC[u] + w + dD[v] == dcd:
                dp[v] = max(dp[v], dp[u] + 1)  # 边成立则 v 必是公共点（见 index.md 证明）
    return max(dp.values(), default=0)      # 没有公共点时答案就是 0


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    g: Graph = [[] for _ in range(n + 1)]
    rg: Graph = [[] for _ in range(n + 1)]
    for _ in range(m):
        x, y, w = next(data), next(data), next(data)
        g[x].append((y, w))
        rg[y].append((x, w))
    A, B, C, D = next(data), next(data), next(data), next(data)

    # dB、dD 是"到 B / 到 D 的距离"，在反图上跑即可
    dA, dB, dC, dD = (dijkstra(A, g, n), dijkstra(B, rg, n),
                      dijkstra(C, g, n), dijkstra(D, rg, n))
    print(max_rewards(g, (dA, dB, dC, dD), (dA[B], dC[D])))


if __name__ == "__main__":
    solve()
