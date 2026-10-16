import sys
from heapq import heappop, heappush

# 边用 (终点 v, 边权 w) 表示
type Edge = tuple[int, int]
# 邻接表：g[u] 是出边列表，Graph 的每个元素本身也是列表
type Graph = list[list[Edge]]


def dijkstra(g: Graph, src: int) -> list[int]:
    infinity = 10**30
    # dis[v] 表示当前已知的 src 到 v 的最短距离，先全部设为无穷
    dis = [infinity for i in range(len(g))]
    dis[src] = 0

    # 小根堆，存放 (距离, 节点)。距离写在前面，元组比较时优先比距离
    heap = [(0, src)]

    while heap:
        disu, u = heappop(heap)
        # 堆里可能有同一个节点的多条旧记录，若弹出距离比 dis[u] 大说明已过期
        if disu > dis[u]:
            continue
        # 用 u 去松弛它的所有出边
        for v, w in g[u]:
            disv = disu + w
            # 只有能让 v 变短才更新，并把新状态压入堆
            if disv < dis[v]:
                dis[v] = disv
                heappush(heap, (disv, v))
    return dis


def solve(data):
    # 依次读出 n 个点、m 条边、起点 s
    n, m, s = next(data), next(data), next(data)
    # 邻接表用 1..n 编号，所以开 n+1 个位置
    g: list[list[Edge]] = [[] for _ in range(n + 1)]
    for _ in range(m):
        u, v, w = next(data), next(data), next(data)
        g[u].append((v, w))

    return dijkstra(g, s)


if __name__ == "__main__":
    # 一次读完输入，切成整数迭代器，比逐行 readline 更快
    data = iter(map(int, sys.stdin.buffer.read().split()))
    dis = solve(data)
    # 起点编号从 1 开始，跳过 dis[0]；不可达的点仍为 infinity
    print(*dis[1:])
