import sys
from heapq import heapify,heappop,heappush


type edge = tuple[int,int]
type Graph = list[list[edge]]

def node_id(id,k,n):
    return id + k *n

# Dijkstra 非负权单源最短路（堆优化），点编号 1..n（dist[0] 不用）。
# dijkstra 返回 (dist, pre)：dist 用 INF 表示不可达，pre[source] = -1，其余前驱在松弛成功时记录。
# 边权必须非负；出现负权边时本文的距离不再可信，应改用 Bellman-Ford 或 SPFA。
# Python 的 int 是任意精度，不必像 C++ 那样用 long long 防溢出。

import heapq

INF = 1 << 62  # 哨兵，比任何合法最短距离都大



def dijkstra(graph: Graph, source: int):
    """返回 (dist, pre)；同一张图换源点可重复调用。"""
    n = len(graph) - 1
    dist = [INF] * (n + 1)
    dist[source] = 0
    heap: list[tuple[int, int]] = [(0, source)]  # (距离, 点编号)，距离在前才能按它比大小

    while heap:
        du, u = heappop(heap)
        if du > dist[u]:
            continue  # 旧记录：这个点已有更短距离，不要再扫它的出边
        for v, w in graph[u]:
            nd = du + w
            if nd < dist[v]:  # 只接受严格改善，零权环上相等距离不再入堆
                dist[v] = nd
                heapq.heappush(heap, (nd, v))

    return dist






def solve(data):
    n, m, k = next(data), next(data), next(data)
    s, t = next(data), next(data)
    total = (k+1) *n
    g:Graph = [ [] for i in range(total)]

    def link(u,v,w):
        g[u].append((v,w))
    def node_id_by_layer(id,layer):
        return id + layer * n;

    for _ in range(m):
        u, v, w = next(data), next(data), next(data)
        
        # 一层一层的建立
        for layer in range(k+1):
            # 当前层
            link( node_id_by_layer(u,layer),node_id_by_layer(v,layer),w)
            link( node_id_by_layer(v,layer),node_id_by_layer(u,layer),w)
            # 和下一层的点建立关系
            if layer+1 <= k:
                # 单向的边
                link( node_id_by_layer(u,layer),node_id_by_layer(v,layer+1),0)
                link( node_id_by_layer(v,layer),node_id_by_layer(u,layer+1),0)

    dist = dijkstra(g,s)
    ans = INF
    for layer in range(k+1):
        ans = min(ans,dist[node_id_by_layer(t,layer)])
    print(ans)

if __name__ == "__main__":
    data = iter(map(int, sys.stdin.buffer.read().split()))
    solve(data)
