#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 12:55
# update_at: 2026-10-01 13:10

import sys


def topo_order(n: int, adj: list[list[int]], indeg: list[int]) -> list[int]:
    """Kahn 算法求拓扑序：反复取出入度为 0 的点，并消掉它伸出的每条边。

    只在内部副本上减入度，调用者的 indeg 原样保留，之后还要当引用计数用。
    """
    deg = indeg[:]
    order: list[int] = []
    queue = [v for v in range(1, n + 1) if deg[v] == 0]
    for u in queue:                    # queue 边遍历边增长，用法等价于 deque
        order.append(u)
        for v in adj[u]:
            deg[v] -= 1
            if deg[v] == 0:
                queue.append(v)
    return order


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    adj: list[list[int]] = [[] for _ in range(n + 1)]
    preds = [0] * (n + 1)              # preds[v]：v 的前驱个数，等于去重后的入度
    edges: set[tuple[int, int]] = set()
    for _ in range(m):
        edge = next(data), next(data)
        if edge in edges:              # 重边只留一条，否则前驱个数会被重复统计
            continue
        edges.add(edge)
        x, y = edge
        adj[x].append(y)
        preds[y] += 1

    # reach[v] 是一个大整数：第 u 位为 1 表示 v 能到达 u。
    # 每个掩码至少要留给 preds[v] 个前驱去读，读完（计数归零）就释放，
    # 否则 N 个 O(N) 位的大整数会同时驻留，内存会翻好几倍。
    reach = [0] * (n + 1)
    count = [0] * (n + 1)
    for v in reversed(topo_order(n, adj, preds)):  # 逆拓扑序：后继的 reach 都已算好
        mask = 1 << v                              # 先把自己放进去
        for w in adj[v]:
            mask |= reach[w]                       # 后继能到的点，v 也都能到
        count[v] = mask.bit_count()                # 二进制里 1 的个数就是可达点数
        for w in adj[v]:
            preds[w] -= 1
            if preds[w] == 0:
                reach[w] = 0                       # w 的前驱都读完了，掩码可以释放
        if preds[v]:
            reach[v] = mask

    sys.stdout.write('\n'.join(map(str, count[1:])))


if __name__ == "__main__":
    solve()
