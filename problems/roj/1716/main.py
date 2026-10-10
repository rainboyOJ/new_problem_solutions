#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 11:05
# update_at: 2026-10-07 11:05

import sys
from heapq import heappop, heappush

INF = 1 << 60  # 距离哨兵：任何真实路径长度都远小于它

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Graph = list[list[tuple[int, int]]]  # 邻接表 g[u] = [(v, w), ...]，重边各占一项


def count_routes(g: Graph, s: int, t: int) -> int:
    """返回 s->t 的「最短路条数 + 次短路恰好多 1 时的次短路条数」。

    每个点拆成两个状态 (u, k)：k=0 最短路、k=1 严格次短路，在状态上跑 Dijkstra。
    边权 >= 1，所以长度为 dist[v][k] 的路线其前驱状态距离严格更小、必先出堆，
    于是 (v,k) 出堆时它的条数已经收齐，出堆后用不着再回头累加。
    """
    n = len(g) - 1  # g 用 1..n 编号，0 号位空占
    dist = [[INF, INF] for _ in range(n + 1)]
    cnt = [[0, 0] for _ in range(n + 1)]  # 与 dist 逐格对应的路线条数
    dist[s][0], cnt[s][0] = 0, 1
    heap = [(0, s, 0)]

    while heap:
        d, u, k = heappop(heap)
        if d != dist[u][k]:
            continue  # 陈旧状态：同一状态已被更短的距离取代
        for v, w in g[u]:
            nd = d + w
            if nd < dist[v][0]:
                if dist[v][0] < dist[v][1]:
                    # 老的最短路退位成次短路，条数一起搬走；此后同长度的贡献
                    # 都会落进下面 nd == dist[v][1] 那一支继续累加
                    dist[v][1], cnt[v][1] = dist[v][0], cnt[v][0]
                    heappush(heap, (dist[v][1], v, 1))
                dist[v][0], cnt[v][0] = nd, cnt[u][k]
                heappush(heap, (nd, v, 0))
            elif nd == dist[v][0]:
                cnt[v][0] += cnt[u][k]  # 另一条等长路线
            elif nd < dist[v][1]:
                dist[v][1], cnt[v][1] = nd, cnt[u][k]
                heappush(heap, (nd, v, 1))
            elif nd == dist[v][1]:
                cnt[v][1] += cnt[u][k]

    if dist[t][1] == dist[t][0] + 1:
        return cnt[t][0] + cnt[t][1]
    return cnt[t][0]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)

    for _ in range(T):
        n, m = next(data), next(data)
        g: Graph = [[] for _ in range(n + 1)]
        for _ in range(m):
            x, y, w = next(data), next(data), next(data)
            g[x].append((y, w))  # 平行边各占一项，天然按「边集不同」区分路线
        s, t = next(data), next(data)
        out.append(str(count_routes(g, s, t)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
