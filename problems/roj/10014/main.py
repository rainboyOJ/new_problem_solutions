#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 22:30
# update_at: 2026-10-10 02:00

import sys
from collections import deque
from collections.abc import Iterator

NEG = -10 ** 18  # 路径权值最低约 -1e5 * 1e9 = -1e14，用 -1e18 当「不可达」

type Adj = list[list[int]]  # adj[u] = u 的出边终点列表（反向图同理）


def read_ints() -> Iterator[int]:
    """逐个产出输入里的整数。"""
    return iter(map(int, sys.stdin.buffer.read().split()))


def topo_order(n: int, adj: Adj) -> list[int]:
    """Kahn 拓扑排序；输入保证无环，返回的长度必定是 n。"""
    indeg = [0] * (n + 1)
    for u in range(1, n + 1):
        for v in adj[u]:
            indeg[v] += 1
    q = deque(u for u in range(1, n + 1) if indeg[u] == 0)
    order = []
    while q:
        u = q.popleft()
        order.append(u)
        for v in adj[u]:
            indeg[v] -= 1
            if indeg[v] == 0:
                q.append(v)
    return order


def best_path(n: int, w: list[int], adj: Adj,
              order: list[int]) -> tuple[list[int], list[int]]:
    """以每个点为终点的最大权路径：返回 (值, 前驱)，前驱指向自己表示路径由此开始。"""
    value = [NEG] * (n + 1)
    pre = list(range(n + 1))
    for u in order:                       # 自己单点开局，或把 u 接到某个前驱之后
        if w[u] > value[u]:
            value[u], pre[u] = w[u], u
        for v in adj[u]:
            if value[v] < w[v] + value[u]:
                value[v], pre[v] = w[v] + value[u], u
    return value, pre


def best_avoiding(n: int, w: list[int], adj: Adj, order: list[int],
                  seeds: list[int], on_path: list[bool]) -> int:
    """在「不含 on_path 上任何点」的子图里，从 seeds 出发求最大权路径（下限 0）。"""
    usable = [False] * (n + 1)
    for v in seeds:
        usable[v] = True
    value = [NEG] * (n + 1)
    for u in order:
        if not usable[u] or on_path[u]:
            continue
        if w[u] > value[u]:
            value[u] = w[u]
        for v in adj[u]:
            if on_path[v]:
                continue
            usable[v] = True
            if value[v] < w[v] + value[u]:
                value[v] = w[v] + value[u]
    return max([0] + value[1:])


def solve() -> None:
    data = read_ints()
    n = next(data)
    m = next(data)
    w = [0] + [next(data) for _ in range(n)]

    adj: Adj = [[] for _ in range(n + 1)]
    radj: Adj = [[] for _ in range(n + 1)]
    for _ in range(m):
        u, v = next(data), next(data)
        adj[u].append(v)
        radj[v].append(u)

    order = topo_order(n, adj)
    rorder = topo_order(n, radj)

    value, pre = best_path(n, w, adj, order)
    # Monster 拿走全图价值最大的那条路径；同值时取编号最小的终点（固定成唯一一条）
    ans1 = max(value[1:])
    if ans1 <= 0:  # 最大路径都非正 ⇒ 双方都打造空项链
        print("0 0")
        return
    r1 = value.index(ans1, 1)

    on_path = [False] * (n + 1)
    u = r1                              # 沿前驱回溯出 Monster 项链占用的点
    while pre[u] != u:
        on_path[u] = True
        u = pre[u]
    on_path[u] = True

    # 接在 Monster 项链后面（从 r1 的后继方向走）或前面（在反向图上从 l1 走）
    ans2 = best_avoiding(n, w, adj, order, adj[r1], on_path)
    ans2 = max(ans2, best_avoiding(n, w, radj, rorder, radj[u], on_path))

    print(ans1, ans2)


if __name__ == "__main__":
    solve()
