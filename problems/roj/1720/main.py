#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 18:13
# update_at: 2026-10-07 18:13

import sys

NO_CYCLE = "PaPaFish is laying egg!"  # 无环时的固定输出
BINARY_STEPS = 40                     # 二分次数：区间 1e7 / 2^40 << 0.005，足够定出两位小数

type Edges = list[tuple[int, int, int]]   # 每条边 (u, v, w)，点从 1 开始编号
type Adj = list[list[tuple[int, int]]]    # 邻接表：adj[u] = [(v, w), ...]


def build_adj(n: int, edges: Edges) -> Adj:
    """把边表转成邻接表，adj[u] 存 u 的所有出边。"""
    adj: Adj = [[] for _ in range(n + 1)]
    for u, v, w in edges:
        adj[u].append((v, w))
    return adj


def has_cycle(n: int, adj: Adj) -> bool:
    """有向图是否有环：三色标记迭代 DFS，0 未访问 / 1 在栈上 / 2 已完成。"""
    color = [0] * (n + 1)
    for s in range(1, n + 1):
        if color[s]:
            continue
        color[s] = 1
        stack = [(s, iter(adj[s]))]              # (顶点, 尚未枚举完的出边迭代器)
        while stack:
            u, it = stack[-1]
            nxt = next(it, None)
            if nxt is None:                      # u 的出边枚举完了
                color[u] = 2
                stack.pop()
            elif color[nxt[0]] == 1:             # 指向栈上的点 ⇒ 有环
                return True
            elif color[nxt[0]] == 0:
                color[nxt[0]] = 1
                stack.append((nxt[0], iter(adj[nxt[0]])))
    return False


def has_negative_cycle(n: int, adj: Adj, lam: float) -> bool:
    """边权换成 w - lam 后是否存在负环（DFS 版 SPFA）。

    dis 全部初始化为 0，相当于加一个 0 权虚拟源点连到所有点，因此不要求图连通。
    松弛 u->v 时若 v 正处在当前 DFS 栈上，说明沿栈走回了 v，这段回路权值为负；
    若 v 不在栈上则带着更小的 dis[v] 继续深入。DFS 版比 BFS 版少一半入队开销，
    Python 下常数小得多；判定语义与 C++ 版的多源 BFS-SPFA 完全一致。
    """
    dis = [0.0] * (n + 1)
    on_stack = bytearray(n + 1)
    for s in range(1, n + 1):
        if on_stack[s]:
            continue
        on_stack[s] = 1
        stack = [(s, iter(adj[s]))]
        while stack:
            u, it = stack[-1]
            nxt = next(it, None)
            if nxt is None:                      # u 的出边枚举完，离开 DFS 栈
                on_stack[u] = 0
                stack.pop()
                continue
            v, w = nxt
            nd = dis[u] + w - lam
            if nd < dis[v] - 1e-12:
                dis[v] = nd
                if on_stack[v]:                  # 回到栈上的点 ⇒ 存在负环
                    return True
                on_stack[v] = 1
                stack.append((v, iter(adj[v])))
    return False


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    edges: Edges = [(next(data), next(data), next(data)) for _ in range(m)]

    adj = build_adj(n, edges)
    if not has_cycle(n, adj):                    # 无环分支先判掉，否则二分结果无意义
        print(NO_CYCLE)
        return

    maxw = max(w for _, _, w in edges)           # 答案一定不超过最大边权（0 <= w）
    lo, hi = 0.0, float(maxw)
    for _ in range(BINARY_STEPS):
        mid = (lo + hi) / 2
        if has_negative_cycle(n, adj, mid):      # 存在负环 ⇒ 答案 <= mid
            hi = mid
        else:
            lo = mid
    print(f"{(lo + hi) / 2:.2f}")


if __name__ == "__main__":
    solve()
