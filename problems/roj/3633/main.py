#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 11:58
# update_at: 2026-10-02 11:58

import sys


def lca(u: int, v: int, depth: list[int], up: list[list[int]]) -> int:
    """树上最近公共祖先：先把深的点抬到同深度，再从高倍跳级同步上跳。"""
    if depth[u] < depth[v]:
        u, v = v, u
    skip = depth[u] - depth[v]
    for k in range(len(up)):
        if skip >> k & 1:
            u = up[k][u]
    if u == v:
        return u
    for k in range(len(up) - 1, -1, -1):  # 最高倍起试，落脚点刚好在 LCA 下方
        if up[k][u] != up[k][v]:
            u, v = up[k][u], up[k][v]
    return up[0][u]


def solve() -> None:
    it = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(it), next(it)

    # 邻接表存 (邻居, 边权)
    g: list[list[tuple[int, int]]] = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        a, b, t = next(it), next(it), next(it)
        g[a].append((b, t))
        g[b].append((a, t))

    # 迭代 DFS：父、深、到根的边权和、到父的边权，order 为前序（父先于子）
    parent = [0] * (n + 1)
    depth = [0] * (n + 1)
    dist = [0] * (n + 1)
    wpar = [0] * (n + 1)
    order: list[int] = []
    stack = [1]
    while stack:
        u = stack.pop()
        order.append(u)
        for v, w in g[u]:
            if v != parent[u]:  # 树上唯一会走回头的边就是连向父节点那条
                parent[v] = u
                depth[v] = depth[u] + 1
                dist[v] = dist[u] + w
                wpar[v] = w
                stack.append(v)

    # 倍增表 up[k][v] = v 的 2^k 级祖先
    up = [parent]
    for _ in range(1, n.bit_length()):
        prev = up[-1]
        up.append([prev[prev[v]] for v in range(n + 1)])

    # 每个运输计划：两端点、LCA、航程长度（LCA 把路径拆成两条上行链）
    pu = [0] * m
    pv = [0] * m
    pl = [0] * m
    lens = [0] * m
    for j in range(m):
        u, v = next(it), next(it)
        w = lca(u, v, depth, up)
        pu[j], pv[j], pl[j] = u, v, w
        lens[j] = dist[u] + dist[v] - 2 * dist[w]

    diff = [0] * (n + 1)  # 树上差分数组，判定之间原地清零复用

    def feasible(limit: int) -> bool:
        """limit 时间内能否完工：找一条被所有超时计划共用、且足够长的虫洞边。"""
        over = 0      # 航程超过 limit 的计划数
        longest = 0   # 它们当中最长的航程
        for j in range(m):
            L = lens[j]
            if L > limit:
                over += 1
                if L > longest:
                    longest = L
                diff[pu[j]] += 1  # 路径差分：两端 +1，LCA -2
                diff[pv[j]] += 1
                diff[pl[j]] -= 2
        if over == 0:
            return True           # 没有超时计划，虫洞放哪都行
        need = longest - limit    # 公共边至少要省掉这么多时间
        best = 0                  # 被全部超时计划覆盖的边里的最大边权
        for v in reversed(order):  # 前序倒着走 = 自底向上汇总子树差分
            d = diff[v]
            diff[v] = 0           # 顺手清零，下一次判定直接复用
            if parent[v]:
                diff[parent[v]] += d
                if d == over and wpar[v] > best:
                    best = wpar[v]
        return best >= need

    # 下界：最长航程无论选哪条边做虫洞都至少剩 max_len - 全局最大边权；上界：不省任何时间
    max_len = max(lens)
    lo, hi = max(0, max_len - max(wpar)), max_len
    while lo < hi:
        mid = (lo + hi) // 2
        if feasible(mid):
            hi = mid
        else:
            lo = mid + 1
    print(lo)


if __name__ == "__main__":
    solve()
