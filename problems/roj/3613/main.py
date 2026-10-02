#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 10:51
# update_at: 2026-10-02 10:51

import heapq
import sys
from collections import deque
from functools import cache

INF = 10**9  # 不可达哨兵：远超棋盘最大步数 n*m


def blank_dist(src: int, blocked: int, adj: list[list[int]], k: int) -> list[int]:
    """空白从 src 出发、避开 blocked（目标棋子所在格）到每个格子的最短步数。"""
    dist = [INF] * k
    dist[src] = 0
    dq = deque([src])
    while dq:
        u = dq.popleft()
        for v in adj[u]:
            if v != blocked and dist[v] > dist[u] + 1:  # 只在可移动格之间行走
                dist[v] = dist[u] + 1
                dq.append(v)
    return dist


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m, q = next(data), next(data), next(data)
    k = n * m
    free = [next(data) for _ in range(k)]  # 1 = 可移动格（含空白），0 = 固定格
    adj: list[list[int]] = [[] for _ in range(k)]
    for i in range(k):
        if free[i]:  # 只有可移动格之间才相邻可达
            r, c = divmod(i, m)
            adj[i] = [
                j
                for j, inside in ((i - 1, c > 0), (i + 1, c < m - 1), (i - m, r > 0), (i + m, r < n - 1))
                if inside and free[j]
            ]

    @cache
    def near_dist(p: int, a: int) -> tuple[int, ...]:
        """空白从邻格 a 绕开棋子 p 后，到 p 各邻格的最短步数（与 adj[p] 对齐）。"""
        dist = blank_dist(a, p, adj, k)
        return tuple(dist[b] for b in adj[p])

    def play(e0: int, s: int, t: int) -> int:
        """一局游戏：在状态 (棋子格 p, 空白邻格 a) 上跑 Dijkstra，返回最少秒数或 -1。"""
        if not free[s] or not free[t] or not free[e0]:
            return -1
        if s == t:  # 棋子已在目标位置
            return 0
        first = blank_dist(e0, s, adj, k)  # 首次推动前，空白绕开 S 的行走距离
        best: dict[tuple[int, int], int] = {}
        pq: list[tuple[int, int, int]] = []
        for a in adj[s]:
            if first[a] < INF:  # 空白走到 S 的某个邻格后才可能推动棋子
                best[(s, a)] = first[a]
                heapq.heappush(pq, (first[a], s, a))
        while pq:
            c, p, a = heapq.heappop(pq)
            if best.get((p, a)) != c:  # 过期堆项
                continue
            if p == t:  # 棋子抵达目标，首次弹出即最短
                return c
            # 棋子走进空白格：空白换到原棋子格 p（p 与 a 相邻，状态不变量保持）
            if c + 1 < best.get((a, p), INF):
                best[(a, p)] = c + 1
                heapq.heappush(pq, (c + 1, a, p))
            # 空白绕开棋子走到 p 的其他邻格，为下一次推动占位
            for b, step in zip(adj[p], near_dist(p, a)):
                if step < INF and c + step < best.get((p, b), INF):
                    best[(p, b)] = c + step
                    heapq.heappush(pq, (c + step, p, b))
        return -1

    out: list[str] = []
    for _ in range(q):
        ex, ey, sx, sy, tx, ty = (next(data) - 1 for _ in range(6))
        out.append(str(play(ex * m + ey, sx * m + sy, tx * m + ty)))
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
