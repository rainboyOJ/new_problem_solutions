#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 01:59
# update_at: 2026-10-02 02:07

import sys
from heapq import heappop, heappush

INF = 10 ** 18  # 不可达哨兵；任何真实路径长度都不超过 10^7


def shortest_from(src: int, adj: list[list[tuple[int, int]]], n: int) -> list[int]:
    """src 到每个点的最短路长度：本题的基准值 base，不可达记 INF。"""
    dist = [INF] * (n + 1)
    dist[src] = 0
    heap = [(0, src)]
    while heap:
        d, u = heappop(heap)
        if d > dist[u]:
            continue
        for w, v in adj[u]:
            nd = d + w
            if nd < dist[v]:
                dist[v] = nd
                heappush(heap, (nd, v))
    return dist


def count_routes(src: int, dst: int, adj: list[list[tuple[int, int]]], n: int) -> int:
    """src→dst 的最短路条数 + 恰好比最短路长 1 的路径条数。

    状态编码 node = 2*v + k：k 表示走到 v 时总长相对 base[v] 已经超出几个单位，
    只可能取 0 或 1。每走一条边 (v→to, 权 w)，新状态由 nd - base[to] 决定；
    超出 1 的路径直接丢弃。因为 base 是最短路，nd ≤ base[to] + 1 时必有
    nd ≥ base[to]，所以 (v, k) 的总长恒等于 base[v] + k，同一状态只会在首次
    到达时入堆。
    """
    base = shortest_from(src, adj, n)
    ways = [0] * (2 * n + 2)
    ways[2 * src] = 1                 # 出发点还处在“最短”这一层
    heap = [(0, 2 * src)]
    while heap:
        d, node = heappop(heap)
        v = node >> 1
        cnt = ways[node]
        for w, to in adj[v]:
            nd = d + w
            over = nd - base[to]      # 这条边让路径相对最短路超前了多少
            if over > 1:
                continue              # 比最短路多出 1 个单位以上，不算
            nxt = 2 * to + over
            if ways[nxt] == 0:        # 首次到达该状态，它的总长 nd 已是定值
                heappush(heap, (nd, nxt))
            ways[nxt] += cnt
    return ways[2 * dst] + ways[2 * dst + 1]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)

    for _ in range(T):
        n, m = next(data), next(data)
        adj: list[list[tuple[int, int]]] = [[] for _ in range(n + 1)]
        for _ in range(m):
            a, b, length = next(data), next(data), next(data)
            adj[a].append((length, b))  # 平行边各自独立，天然计入不同线路
        s, f = next(data), next(data)
        out.append(str(count_routes(s, f, adj, n)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
