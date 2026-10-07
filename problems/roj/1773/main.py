#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 01:41
# update_at: 2026-10-08 01:41

import sys

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Tree = list[list[int]]  # 邻接表：Tree[u] 是 u 的所有邻居（下标 0 空置）


def root_order(adj: Tree) -> tuple[list[int], list[int]]:
    """以 1 为根 BFS 定序，返回 (访问序, 父亲数组)，父亲一定排在儿子前面。"""
    par = [0] * len(adj)
    order = [1]
    for u in order:
        for v in adj[u]:
            if v != par[u]:
                par[v] = u
                order.append(v)
    return order, par


def subtree_time(adj: Tree, par: list[int], order: list[int]) -> list[int]:
    """f[u]：u 在 0 时刻已知消息时，u 的子树全部知情所需的时间。

    儿子降序发送：第 i 个儿子在第 i 秒被通知，故 f[u] = max(i + f_i)，叶子为 0。
    """
    f = [0] * len(adj)
    for u in reversed(order):
        sons = sorted((f[v] for v in adj[u] if v != par[u]), reverse=True)
        f[u] = max((i + x for i, x in enumerate(sons, 1)), default=0)
    return f


def reroot(adj: Tree, par: list[int], order: list[int], f: list[int]) -> list[int]:
    """自顶向下换根，返回 g[u]：u 在 0 时刻已知消息时传遍全树的时间。

    把 u 的所有方向降序排成 w[1..m]（儿子方向取 f[son]，父亲方向取 up[u]），则
    pref[i] = max(j + w_j) (j<=i)、suff[i] = max(j-1 + w_j) (j>=i)；
    剔除第 idx 位的儿子 v 后，后面各项集体前移一位，于是
    up[v] = max(pref[idx-1], suff[idx+1])，而 g[u] = pref[m]。
    """
    up = [0] * len(adj)
    g = [0] * len(adj)
    for u in order:
        items = sorted(
            ((up[u] if v == par[u] else f[v], v) for v in adj[u]),  # (方向耗时, 邻居)
            reverse=True,
        )
        m = len(items)
        pref = [0] * (m + 1)
        for i in range(1, m + 1):
            pref[i] = max(pref[i - 1], i + items[i - 1][0])
        suff = [0] * (m + 2)
        for i in range(m, 0, -1):
            suff[i] = max(suff[i + 1], i - 1 + items[i - 1][0])  # -1：删一项后整体前移
        g[u] = pref[m]
        for i in range(1, m + 1):
            v = items[i - 1][1]
            if par[v] == u:  # v 是 u 的儿子，它拿到的正是"父亲方向"耗时
                up[v] = max(pref[i - 1], suff[i + 1])
    return g


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    adj: Tree = [[] for _ in range(n + 1)]
    for i in range(2, n + 1):
        p = next(data)  # 编号 i 的人的直接上级
        adj[p].append(i)
        adj[i].append(p)  # 消息双向可传，按无向边建树
    order, par = root_order(adj)
    g = reroot(adj, par, order, subtree_time(adj, par, order))
    best = min(g[1:])
    print(1 + best)  # 最初通知那个人要花 1 单位时间
    print(" ".join(str(u) for u in range(1, n + 1) if g[u] == best))


if __name__ == "__main__":
    solve()
