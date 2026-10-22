#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-21 20:10
# update_at: 2026-10-21 20:10

import sys
from collections import deque

type Info = tuple[int, int]  # (路径最大边权, 严格次大边权)，-1 表示不存在（边权可为 0）

NEG = -1  # 「不存在」哨兵：边权 >= 0，所以 -1 一定不与真实权值混淆


def merge(a: Info, b: Info) -> Info:
    """合并两段路径的最值信息，返回 (最大, 严格次大)。

    次大必须排除与最大等值的重复边——「严格」二字在数据结构层的落点。
    哨兵 -1 比任何真实权值都小，自然不会当上最大，只会被淘汰。
    """
    first = max(a[0], b[0])
    cands = (a[0], a[1], b[0], b[1])
    second = max((c for c in cands if c < first), default=NEG)
    return first, second


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    if n == 1:  # 单点无树边，严格次小生成树不存在
        print(-1)
        return

    # edges[i] = (u, v, w, 是否树边)；先读入再排序，in_mst 之后写回
    edges = [(next(data), next(data), next(data), False) for _ in range(m)]

    # ---- 1. Kruskal 求 MST ----
    parent = list(range(n + 1))  # parent[x]：并查集父指针

    def find(x: int) -> int:
        while parent[x] != x:
            parent[x] = parent[parent[x]]  # 路径压缩（隔代跳）
            x = parent[x]
        return x

    order = sorted(range(m), key=lambda i: edges[i][2])  # 按边权非降序处理
    mst_sum, picked = 0, 0
    for i in order:
        u, v, w, _ = edges[i]
        ru, rv = find(u), find(v)
        if ru == rv:  # 两端已连通（含自环），选它成环，跳过
            continue
        parent[ru] = rv
        mst_sum += w
        edges[i] = (u, v, w, True)
        picked += 1
        if picked == n - 1:  # 生成树恰好 n-1 条边，选满即停
            break

    # ---- 2. 用树边建邻接表，BFS 求深度/父边（迭代，不吃递归栈） ----
    adj: list[list[tuple[int, int]]] = [[] for _ in range(n + 1)]
    for u, v, w, in_mst in edges:
        if in_mst:
            adj[u].append((v, w))
            adj[v].append((u, w))

    LOG = max(1, (n - 1).bit_length()) if n > 1 else 1  # 2^LOG >= 最大深度
    depth = [0] * (n + 1)
    up = [[0] * (LOG + 1) for _ in range(n + 1)]    # up[u][j]：u 的第 2^j 级祖先
    info = [[(NEG, NEG)] * (LOG + 1) for _ in range(n + 1)]  # u 向上 2^j 条边的 (最大, 严格次大)

    depth[1], up[1][0], info[1][0] = 1, 0, (NEG, NEG)  # 根的父边哨兵
    queue = deque([1])
    while queue:
        u = queue.popleft()
        for v, w in adj[u]:
            if depth[v]:  # 已访问（父方向）
                continue
            depth[v] = depth[u] + 1
            up[v][0] = u
            info[v][0] = (w, NEG)  # 一条边没有次大
            queue.append(v)

    for j in range(1, LOG + 1):
        for i in range(1, n + 1):
            mid = up[i][j - 1]
            up[i][j] = up[mid][j - 1]
            info[i][j] = merge(info[i][j - 1], info[mid][j - 1])

    # ---- 3. 枚举非树边，换掉路径上「严格小于 w 的最大边」 ----
    def path_info(u: int, v: int) -> Info:
        """树上 u~v 路径的 (最大边权, 严格次大边权)。"""
        res: Info = (NEG, NEG)
        if depth[u] < depth[v]:
            u, v = v, u
        for j in range(LOG, -1, -1):  # u 跳到与 v 同层
            if depth[u] - depth[v] >= 1 << j:
                res = merge(res, info[u][j])
                u = up[u][j]
        if u == v:
            return res
        for j in range(LOG, -1, -1):  # 一起向上跳
            if up[u][j] != up[v][j]:
                res = merge(res, merge(info[u][j], info[v][j]))
                u, v = up[u][j], up[v][j]
        return merge(res, merge(info[u][0], info[v][0]))  # 补两条连向 LCA 的父边

    ans = -1  # 无解时保持 -1（题面保证存在，对拍覆盖无解情形）
    for u, v, w, in_mst in edges:
        if in_mst or u == v:  # 自环进不了任何生成树
            continue
        first, second = path_info(u, v)
        if w > first:
            cand = mst_sum - first + w  # 换最大边
        elif w == first and second != NEG:
            cand = mst_sum - second + w  # 换最大边增量 0，退到严格次大
        else:  # w < first 不可能发生；w == first 且无次大则该边无法严格替换
            continue
        ans = cand if ans < 0 or cand < ans else ans

    print(ans)


if __name__ == "__main__":
    solve()
