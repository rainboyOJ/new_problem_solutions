#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys
import heapq
from collections.abc import Iterator


def h_values(t: int, radj: list[list[tuple[int, int]]]) -> list[int | None]:
    """反图 Dijkstra：h[v] = v 到终点 t 的最短路，作为 A* 的启发函数。"""
    h: list[int | None] = [None] * len(radj)
    h[t] = 0
    pq = [(0, t)]
    while pq:
        d, u = heapq.heappop(pq)
        if h[u] != d:  # 过期堆条目
            continue
        for v, w in radj[u]:
            if h[v] is None or d + w < h[v]:
                h[v] = d + w
                heapq.heappush(pq, (h[v], v))
    return h


def kth_walks(s: int, t: int, k: int, adj: list[list[tuple[int, int]]],
              h: list[int | None]) -> Iterator[int]:
    """A* 依次产出从 s 走到 t 的各条路径长度（按不降序，含重复），最多产出 k 条。

    堆条目 (f, g, u)：f = g + h[u]。h 可采纳且一致（边权满足三角不等式），
    所以第 cnt 次弹出 t 时，g 恰好是第 cnt 短的路长。
    """
    cnt = 0
    heap = [(h[s], 0, s)]
    while heap:
        f, g, u = heapq.heappop(heap)
        if u == t and g > 0:  # g>0 排除 s==t 时的零边平凡"路径"（题目要求至少一条边）
            cnt += 1
            yield g
            if cnt == k:
                return
        for v, w in adj[u]:
            if h[v] is not None:  # v 到不了 t，扩展它永远不会到达答案
                heapq.heappush(heap, (g + w + h[v], g + w, v))


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    adj = [[] for _ in range(n + 1)]   # 正图：沿路径方向走
    radj = [[] for _ in range(n + 1)]  # 反图：从终点倒着求 h
    for _ in range(m):
        a, b, l = next(data), next(data), next(data)
        adj[a].append((b, l))
        radj[b].append((a, l))

    s, t, k = next(data), next(data), next(data)

    h = h_values(t, radj)
    if h[s] is None:  # 起点连一条到终点的路都没有，任何条数的路都不存在
        print(-1)
        return
    found = list(kth_walks(s, t, k, adj, h))  # 生成器最多产出 k 条，取尽即停
    print(found[-1] if len(found) == k else -1)


if __name__ == "__main__":
    solve()
