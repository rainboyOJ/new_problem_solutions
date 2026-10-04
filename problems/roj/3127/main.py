#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 19:10
# update_at: 2026-10-01 19:10

import sys
from array import array

INF = 1 << 30  # 边数上界（简单路径最多 n-1 条边）：best 的空位和「无解」都记成它


def centroid_of(head: array, nxt: array, to: array, removed: bytearray,
                par: array, sz: array, root: int) -> int:
    """求 root 所在分量的重心：删掉它以后，剩下的每一块规模都不超过总量的一半。"""
    par[root] = root
    sz[root] = 0
    order = [root]                                 # order 边遍历边增长，等价于手写栈
    for u in order:
        e = head[u]
        while e != -1:
            v = to[e]
            if not removed[v] and v != par[u]:
                par[v] = u
                sz[v] = 0                          # 先归零，下一轮倒序累加才是干净的
                order.append(v)
            e = nxt[e]

    for u in reversed(order):                      # 子节点一定排在父节点后面，可后序累加
        sz[u] += 1
        if u != root:
            sz[par[u]] += sz[u]

    total = sz[root]
    cent = root
    while True:
        heavy, best_sub = -1, 0
        up = total - sz[cent]                      # 父节点方向那一块的规模
        e = head[cent]
        while e != -1:
            v = to[e]
            if not removed[v]:
                sub = up if v == par[cent] else sz[v]
                if sub > best_sub:
                    heavy, best_sub = v, sub
            e = nxt[e]
        if best_sub * 2 <= total:                  # 没有任何一块超过一半：重心已找到
            return cent
        cent = heavy


def scan_subtree(head: array, nxt: array, to: array, wt: array, removed: bytearray,
                 par: array, dist: array, cnt: array, best: array,
                 k: int, cent: int, first: int, w0: int) -> tuple[list[int], int]:
    """扫描重心的一棵子树（首边权 w0），返回 (子树内的点, 子树内查到的最优边数)。

    只看距离不超过 k 的点；拼路径时查询的 best 只含重心和更早处理的子树，
    所以同一棵子树内部的两个点不会在此配成路径。
    """
    nodes: list[int] = []
    par[first], dist[first], cnt[first] = cent, w0, 1
    here = INF
    stack = [first]
    while stack:
        u = stack.pop()
        nodes.append(u)
        du, cu = dist[u], cnt[u]
        cand = cu + best[k - du]                   # 与重心或更早的子树拼成一条经过重心的路径
        if cand < here:
            here = cand
        e = head[u]
        while e != -1:
            x = to[e]
            if not removed[x] and x != par[u]:
                dx = du + wt[e]
                if dx <= k:                        # 权值非负，更深的点只会更远，可整枝剪掉
                    par[x], dist[x], cnt[x] = u, dx, cu + 1
                    stack.append(x)
            e = nxt[e]
    return nodes, here


def min_edges(head: array, nxt: array, to: array, wt: array, n: int, k: int) -> int:
    """点分治：返回边权和恰为 k 的简单路径的最少边数，不存在则返回 INF。"""
    removed = bytearray(n)
    par = array('i', bytes(4 * n))
    sz = array('i', bytes(4 * n))
    dist = array('i', bytes(4 * n))
    cnt = array('i', bytes(4 * n))
    best = array('i', [INF]) * (k + 1)             # best[d] = 已处理部分中距离为 d 的最少边数
    todo = [0]
    ans = INF

    while todo:
        root = todo.pop()
        if removed[root]:                          # 该点已在更早的层里当过重心
            continue
        cent = centroid_of(head, nxt, to, removed, par, sz, root)

        best[0] = 0                                # 重心自身：距离 0，边数 0
        touched = [0]
        e = head[cent]
        while e != -1:                             # 逐棵子树「先查询、后合并」，避免同子树配对
            v = to[e]
            if not removed[v] and wt[e] <= k:      # 首边就超过 k，整棵子树都不可能凑出 k
                nodes, here = scan_subtree(head, nxt, to, wt, removed, par, dist, cnt,
                                           best, k, cent, v, wt[e])
                if here < ans:
                    ans = here
                for u in nodes:                    # 本子树内部的两点留给更深层，此处只登记
                    d = dist[u]
                    if cnt[u] < best[d]:
                        if best[d] == INF:
                            touched.append(d)
                        best[d] = cnt[u]
            e = nxt[e]

        for d in touched:                          # 只擦本层写过的格子，免去每次 O(k) 清空
            best[d] = INF
        removed[cent] = 1
        e = head[cent]                             # 删掉重心：每个邻居各自代表一个新分量
        while e != -1:
            if not removed[to[e]]:
                todo.append(to[e])
            e = nxt[e]

    return ans


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, k = next(data), next(data)

    # 链式前向星：head[u] 是 u 的第一条弧，每条无向边拆成方向相反的两条弧
    head = array('i', [-1]) * n
    to = array('i', bytes(8 * (n - 1)))
    wt = array('i', bytes(8 * (n - 1)))
    nxt = array('i', bytes(8 * (n - 1)))
    for i in range(0, 2 * (n - 1), 2):
        u, v, w = next(data), next(data), next(data)
        to[i], wt[i], nxt[i], head[u] = v, w, head[u], i
        to[i + 1], wt[i + 1], nxt[i + 1], head[v] = u, w, head[v], i + 1

    ans = min_edges(head, nxt, to, wt, n, k)
    print(ans if ans < INF else -1)


if __name__ == "__main__":
    solve()
