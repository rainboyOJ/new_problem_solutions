#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 07:33
# update_at: 2026-10-08 07:33

import sys

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Adj = list[list[int]]  # 邻接表：adj[u] 是 u 的全部出边终点


def reachable_from(adj: Adj, s: int) -> bytearray:
    """从起点 s 出发搜索全图，返回标记可达点的紧凑数组（下标即点编号，1 表示可达）。

    有向图上单源可达性，BFS/DFS 等价；这里用列表当栈，避免递归改写成迭代。
    起点自身先标记（路径长度可为 0），入栈时即标记，保证每个点最多进栈一次。
    """
    seen = bytearray(len(adj))  # 下标 0 空着不用，点编号从 1 开始
    seen[s] = 1
    stack = [s]
    while stack:
        u = stack.pop()
        for v in adj[u]:
            if not seen[v]:  # 入栈同时标记，避免同一个点被重复压栈
                seen[v] = 1
                stack.append(v)
    return seen


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m, k = next(data), next(data), next(data)

    adj: Adj = [[] for _ in range(n + 1)]
    for _ in range(m):
        u = next(data)
        v = next(data)
        adj[u].append(v)  # 有向边，只记 u -> v 这一个方向

    # 每个起点各搜一次，得到全源可达性；下标 0 位空着，与非规格输入无歧义
    reach = [reachable_from(adj, s) for s in range(n + 1)]

    out: list[str] = []
    for _ in range(k):
        x = next(data)
        y = next(data)
        out.append("Yes" if reach[x][y] else "No")
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
