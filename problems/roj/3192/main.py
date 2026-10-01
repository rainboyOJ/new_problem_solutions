#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 01:20
# update_at: 2026-10-02 01:20

import sys
from itertools import accumulate

# 方树编号约定：1..n 是原来的房屋（圆点），n+1..n+rings 是每个环缩成的方点。


def read_graph(xs: list[int], ys: list[int], ws: list[int], n: int, m: int):
    """把 M 条边做成 CSR 邻接表：head[v] 是 v 的出边在 to/wt/eid 里的起始下标。"""
    deg = [0] * (n + 2)
    for x, y in zip(xs, ys):
        deg[x] += 1
        deg[y] += 1
    head = [0, 0] + list(accumulate(deg[1 : n + 1]))  # head[v+1] = head[v] + deg[v]
    fill = head[:]
    to, wt, eid = [0] * (2 * m), [0] * (2 * m), [0] * (2 * m)
    for i, (x, y, w) in enumerate(zip(xs, ys, ws)):
        j = fill[x]
        to[j], wt[j], eid[j], fill[x] = y, w, i, j + 1
        j = fill[y]
        to[j], wt[j], eid[j], fill[y] = x, w, i, j + 1
    return head, to, wt, eid


def find_rings(n: int, head, to, wt, eid):
    """迭代 DFS 建生成树，再让每条非树边圈出它所在的环。

    非树边 (top, bottom) 的浅端点是环顶、深端点是环底，环 = 生成树 top..bottom 这一段
    加上这条非树边；每个环返回「环顶点表（环顶在前）」和「环顶沿生成树到各点的距离」。
    """
    par, pare, dep, dtree = [0] * (n + 1), [-1] * (n + 1), [0] * (n + 1), [0] * (n + 1)
    rings: list[list[int]] = []
    arcs: list[list[int]] = []
    ring_w: list[int] = []
    seen, used = bytearray(n + 1), bytearray(len(eid))  # used：已认领为「非树边」的边
    seen[1] = 1
    ptr, stack = head[:], [1]
    while stack:
        v = stack[-1]
        j = ptr[v]
        if j >= head[v + 1]:  # v 的出边扫完了
            stack.pop()
            continue
        ptr[v] = j + 1
        if eid[j] == pare[v]:  # 这条正是通向父节点的树边
            continue
        u = to[j]
        if seen[u]:
            if not used[eid[j]]:  # 两端都访问过，它就是非树边
                used[eid[j]] = 1
                top, bottom = (u, v) if dep[u] < dep[v] else (v, u)
                nodes, arc = [bottom], [dtree[bottom] - dtree[top]]
                x = par[bottom]
                while x != top:
                    nodes.append(x)
                    arc.append(dtree[x] - dtree[top])
                    x = par[x]
                nodes.append(top)
                arc.append(0)
                nodes.reverse()  # 排成从环顶到环底
                arc.reverse()
                rings.append(nodes)
                arcs.append(arc)
                ring_w.append(arc[-1] + wt[j])  # 生成树弧长 + 非树边 = 真环长
            continue
        seen[u] = 1
        par[u], pare[u], dep[u] = v, eid[j], dep[v] + 1
        dtree[u] = dtree[v] + wt[j]
        stack.append(u)
    return par, dtree, rings, arcs, ring_w


def build_square_tree(n: int, par, dtree, rings, arcs, ring_w):
    """每个环缩成一个挂在环顶下的方点，得到圆方树。

    非环点的父节点就是生成树父节点；环上非顶点的父节点是方点，父边权取「环顶沿环内
    最短路到它」的距离，于是根到各点的方树距离恰好等于仙人掌上的最短路。
    """
    tot = n + len(rings)
    sq_par, sq_w, sq_pos = [0] * (tot + 1), [0] * (tot + 1), [0] * (tot + 1)
    for v in range(2, n + 1):
        sq_par[v] = par[v]
        sq_w[v] = dtree[v] - dtree[par[v]]  # 不在环里的点：父边就是生成树的边
    for r, (nodes, arc) in enumerate(zip(rings, arcs), 1):
        S = n + r
        L = ring_w[r - 1]
        sq_par[S] = nodes[0]  # 方点挂在环顶下，边权 0
        for t, pos in zip(nodes[1:], arc[1:]):
            sq_par[t] = S
            sq_w[t] = min(pos, L - pos)  # 环顶到 t 的两条弧取短
            sq_pos[t] = pos  # t 在「父环」上的弧长坐标，供方点 LCA 的询问用
    children = [[] for _ in range(tot + 1)]
    for v in range(2, tot + 1):
        children[sq_par[v]].append(v)
    sq_dep, sd = [0] * (tot + 1), [0] * (tot + 1)
    order, i = [1], 0
    while i < len(order):  # 层序遍历，同时算方树深度与根到点最短路
        v = order[i]
        i += 1
        for c in children[v]:
            sq_dep[c] = sq_dep[v] + 1
            sd[c] = sd[v] + sq_w[c]
            order.append(c)
    return sq_par, sq_dep, sd, sq_pos, tot


def up_k(up, x: int, k: int) -> int:
    """在方树上把 x 向上跳恰好 k 步（二进制拆分）。"""
    i = 0
    while k:
        if k & 1:
            x = up[i][x]
        k >>= 1
        i += 1
    return x


def lca(up, sq_dep: list[int], log: int, x: int, y: int) -> int:
    """圆方树上 x 与 y 的最近公共祖先。"""
    if sq_dep[x] < sq_dep[y]:
        x, y = y, x
    x = up_k(up, x, sq_dep[x] - sq_dep[y])
    if x == y:
        return x
    for i in range(log - 1, -1, -1):
        if up[i][x] != up[i][y]:
            x, y = up[i][x], up[i][y]
    return up[0][x]


def solve() -> None:
    vals = list(map(int, sys.stdin.buffer.read().split()))
    n, m, q = vals[:3]
    xs, ys, ws = (vals[p::3][:m] for p in (3, 4, 5))  # 三条等差切片取出 x/y/w 三列
    head, to, wt, eid = read_graph(xs, ys, ws, n, m)
    par, dtree, rings, arcs, ring_w = find_rings(n, head, to, wt, eid)
    sq_par, sq_dep, sd, sq_pos, tot = build_square_tree(n, par, dtree, rings, arcs, ring_w)

    log = max(1, tot.bit_length())
    up = [sq_par]  # up[k][v] = v 的 2^k 级祖先，up[0] 就是父指针
    for _ in range(1, log):
        prev = up[-1]
        up.append([prev[prev[v]] for v in range(tot + 1)])

    out: list[int] = []
    rest = vals[3 + 3 * m :]
    for x, y in zip(rest[::2], rest[1::2]):
        a = lca(up, sq_dep, log, x, y)
        if a <= n:  # LCA 是圆点：两端最短路互不干扰，直接由方树距离相减
            out.append(sd[x] + sd[y] - 2 * sd[a])
        else:  # LCA 是方点：要看清两端各自从环的哪个点进来，再在环内选一条弧
            ax = up_k(up, x, sq_dep[x] - sq_dep[a] - 1)
            ay = up_k(up, y, sq_dep[y] - sq_dep[a] - 1)
            d = abs(sq_pos[ax] - sq_pos[ay])
            out.append(sd[x] + sd[y] - sd[ax] - sd[ay] + min(d, ring_w[a - n - 1] - d))
    sys.stdout.write("\n".join(map(str, out)) + "\n")


if __name__ == "__main__":
    solve()
