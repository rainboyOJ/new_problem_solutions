#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 21:55
# update_at: 2026-10-07 21:55

import sys

ROOT = 1  # MST 的根取城市 1；图保证连通，根取谁都不影响路径上的最大边权

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Edge = tuple[int, int, int]        # (u, v, w) 一条双向道路及其过路费
type Adj = list[list[tuple[int, int]]]  # adj[u] = [(相邻城市, 这条路的费用), ...]
type Jump = list[list[int]]             # jump[k][v] = v 向上跳 2^k 步的祖先 / 这段最大边权


def find_root(parent: list[int], x: int) -> int:
    """并查集查根（带路径压缩），Kruskal 用它判断两个城市是否已经连通。"""
    root = x
    while parent[root] != root:
        root = parent[root]
    while parent[x] != root:
        parent[x], x = root, parent[x]
    return root


def build_mst(n: int, edges: list[Edge]) -> Adj:
    """Kruskal 求最小生成树，返回它的邻接表。

    最小生成树就是最小瓶颈生成树：MST 上 u-v 路径的最大边权等于全图所有 u-v 路径
    最大边权的最小值，所以"最少过路费"完全由 MST 决定，与其它边无关。
    """
    parent = list(range(n + 1))
    adj: Adj = [[] for _ in range(n + 1)]
    for u, v, w in sorted(edges, key=lambda e: e[2]):  # 按费用从小到大加边
        ru, rv = find_root(parent, u), find_root(parent, v)
        if ru == rv:
            continue  # 已成环（含自环），这条边不属于 MST
        parent[ru] = rv
        adj[u].append((v, w))
        adj[v].append((u, w))
    return adj


def orient_tree(adj: Adj, n: int) -> tuple[list[int], list[int], list[int]]:
    """把 MST 以 ROOT 为根定向，返回 (深度, 父亲, 到父亲的边权)。

    用显式栈迭代，链状数据不会爆递归栈。
    """
    depth = [0] * (n + 1)
    up0 = [ROOT] * (n + 1)  # 默认祖先为根：题面保证连通，这里只是防越界
    mx0 = [0] * (n + 1)
    seen = [False] * (n + 1)
    seen[ROOT] = True
    stack = [ROOT]
    while stack:
        u = stack.pop()
        for v, w in adj[u]:
            if seen[v]:
                continue
            seen[v] = True
            depth[v] = depth[u] + 1
            up0[v], mx0[v] = u, w
            stack.append(v)
    return depth, up0, mx0


def build_jump(up0: list[int], mx0: list[int]) -> tuple[Jump, Jump]:
    """倍增表：up[k][v] = v 向上 2^k 步的祖先，mx[k][v] = 这 2^k 步里的最大边权。"""
    up, mx = [up0], [mx0]
    for _ in range(1, len(up0).bit_length()):
        prev_up, prev_mx = up[-1], mx[-1]
        up.append([prev_up[x] for x in prev_up])                   # 祖先表翻倍
        mx.append([max(m, prev_mx[x]) for m, x in zip(prev_mx, prev_up)])  # 两段取最大
    return up, mx


def path_max(up: Jump, mx: Jump, depth: list[int], s: int, t: int) -> int:
    """S -> T 在 MST 上的路径最大边权，就是最少过路费；S == T 时为 0。"""
    if s == t:
        return 0  # 原地不动，不用交过路费
    a, b = (s, t) if depth[s] >= depth[t] else (t, s)
    ans = 0
    diff = depth[a] - depth[b]
    for k in range(diff.bit_length()):  # 先把 a 抬到与 b 同深度
        if diff >> k & 1:
            ans = max(ans, mx[k][a])
            a = up[k][a]
    if a == b:
        return ans  # b 就是 a 的祖先，LCA 已找到
    for k in range(len(up) - 1, -1, -1):  # 一起往上跳，停在 LCA 的下一层
        if up[k][a] != up[k][b]:
            ans = max(ans, mx[k][a], mx[k][b])
            a, b = up[k][a], up[k][b]
    return max(ans, mx[0][a], mx[0][b])  # 再各走一步到 LCA


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    edges: list[Edge] = [(next(data), next(data), next(data)) for _ in range(m)]

    depth, up0, mx0 = orient_tree(build_mst(n, edges), n)
    up, mx = build_jump(up0, mx0)

    q = next(data)
    ans = [str(path_max(up, mx, depth, next(data), next(data))) for _ in range(q)]
    print('\n'.join(ans))


if __name__ == "__main__":
    solve()
