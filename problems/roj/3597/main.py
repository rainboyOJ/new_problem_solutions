#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 09:55
# update_at: 2026-10-02 09:55

import sys
from heapq import heappop, heappush
from collections import deque

INF = float("inf")
BIG = 10 ** 9  # 启发式不可达哨兵：任何路径长度都小于它


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, k, m, s, t = (next(data) for _ in range(5))

    culture = [0] + [next(data) for _ in range(n)]  # 国家 i 的文化（下标从 1 起）
    # reject[i][j] = 1 表示文化 i 排斥文化 j（学过 i 就进不了文化 j 的国家）
    reject = [[0] * (k + 1)] + [[0] + [next(data) for _ in range(k)] for _ in range(k)]

    adj: list[list[tuple[int, int]]] = [[] for _ in range(n + 1)]
    for _ in range(m):
        u, v, d = next(data), next(data), next(data)
        adj[u].append((v, d))
        adj[v].append((u, d))

    seen = [False] * (n + 1)  # 忽略文化的地理连通块（必要条件剪枝用）
    seen[s] = True
    bfs = deque([s])
    while bfs:
        for v, _ in adj[u := bfs.popleft()]:
            if not seen[v]:
                seen[v] = True
                bfs.append(v)
    if not seen[t]:
        print(-1)  # 地理上就不连通，与文化无关
        return

    # 终点的最后一跳是必要条件：必须存在某个可达国家 w 与 t 相邻，
    # 且 c[w]≠c[t]、c[w] 不排斥 c[t]，否则任何路径都无法进入终点。
    last_hop = [
        w
        for w in range(1, n + 1)
        if seen[w] and culture[w] != culture[t] and not reject[culture[w]][culture[t]]
        if any(v == t for v, _ in adj[w])
    ]
    if not last_hop:
        print(-1)
        return

    # A* 启发函数：h[u] = 忽略全部文化限制时 u 到 t 的最短距离，是真实剩余距离的下界。
    h = [BIG] * (n + 1)
    h[t] = 0
    heap = [(0, t)]
    while heap:
        du, u = heappop(heap)
        if du > h[u]:
            continue
        for v, d in adj[u]:
            if du + d < h[v]:
                h[v] = du + d
                heappush(heap, (du + d, v))

    # 状态 = (国家, 已学文化集合 mask)，mask 是 Python 大整数位集；
    # 代价 f = 已走路程 + h[u]（地理下界），按 f 从小到大扩展。
    start_mask = 1 << culture[s]
    best: dict[tuple[int, int], int] = {(s, start_mask): 0}
    heap = [(h[s], 0, s, start_mask)]
    while heap:
        f, dist, u, mask = heappop(heap)
        if u == t:  # 到达终点时终点文化已计入 mask
            print(dist)
            return
        if best.get((u, mask), INF) < dist:
            continue
        for v, d in adj[u]:
            c = culture[v]
            if mask >> c & 1:  # 已学过该文化，不能再进
                continue
            if reject[culture[u]][c]:  # 当前文化排斥 v 的文化
                continue
            nmask = mask | 1 << c
            nd = dist + d
            if best.get((v, nmask), INF) > nd:
                best[(v, nmask)] = nd
                # 启发值可进不可退：f 沿每条边至少加 d，队列按 f 排序不违反 Dijkstra 顺序
                heappush(heap, (nd + h[v], nd, v, nmask))
    print(-1)


if __name__ == "__main__":
    solve()
