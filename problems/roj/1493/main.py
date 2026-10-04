#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 14:40
# update_at: 2026-09-30 14:40

import sys

NEG = -1    # 哨兵：这一段路径上不存在"更小的第二条边"（边权非负，-1 必小于任何真实边权）
LOG = 17    # 倍增层数：2^17 = 131072 > 1e5，覆盖全部点数
INF = 10**18  # 答案初始值：边权和上限 3e5 * 1e9 = 3e14


def find(fa: list[int], x: int) -> int:
    """并查集查根：隔代路径压缩，把查询路径直接挂到根下。"""
    while fa[x] != x:
        fa[x] = fa[fa[x]]
        x = fa[x]
    return x


def merge_top2(left: tuple[int, int], right: tuple[int, int]) -> tuple[int, int]:
    """合并两段路径，得到并集的 (最大边权, 严格小于最大的次大边权)。"""
    big = left[0] if left[0] > right[0] else right[0]
    # 谁不是最大值，谁才可能当次大：本段最大值等于全局最大时，只能用本段的次大顶上
    cand_l = left[0] if left[0] < big else left[1]
    cand_r = right[0] if right[0] < big else right[1]
    return big, cand_l if cand_l > cand_r else cand_r


def kruskal(
    edges: list[tuple[int, int, int]], n: int
) -> tuple[int, list[list[tuple[int, int]]], list[tuple[int, int, int]]]:
    """按 (权值, 端点) 升序贪心：选中的边写进生成树邻接表，落选的边就是候选替换边。"""
    fa = list(range(n))
    g: list[list[tuple[int, int]]] = [[] for _ in range(n)]
    light: list[tuple[int, int, int]] = []
    total = 0
    edges.sort()
    for w, a, b in edges:
        ra, rb = find(fa, a), find(fa, b)
        if ra != rb:
            fa[ra] = rb
            total += w
            g[a].append((b, w))
            g[b].append((a, w))
        else:
            light.append((a, b, w))
    return total, g, light


def build_lifting(
    g: list[list[tuple[int, int]]],
) -> tuple[list[int], list[list[int]], list[list[int]], list[list[int]]]:
    """从 0 号点定根 DFS，建倍增表：up 是 2^k 级祖先，mx/m2 是对应段的最大/严格次大边权。"""
    n = len(g)
    depth = [0] * n
    parent = [-1] * n        # -1 表示还没访问过
    w0 = [NEG] * n           # 到父节点的边权，根节点没有
    parent[0] = 0
    stack = [0]
    while stack:
        a = stack.pop()
        for b, w in g[a]:
            if parent[b] < 0:
                parent[b] = a
                w0[b] = w
                depth[b] = depth[a] + 1
                stack.append(b)

    up = [parent]
    mx = [w0]
    m2 = [[NEG] * n]         # 单条边的段里没有第二条边可当次大
    for _ in range(1, LOG):
        prev_up, prev_mx, prev_m2 = up[-1], mx[-1], m2[-1]
        cur_up, cur_mx, cur_m2 = [0] * n, [0] * n, [0] * n
        for v in range(n):
            p = prev_up[v]
            cur_up[v] = prev_up[p]  # 2^(k-1) 级祖先再跳 2^(k-1) 级 = 2^k 级祖先
            cur_mx[v], cur_m2[v] = merge_top2(
                (prev_mx[v], prev_m2[v]), (prev_mx[p], prev_m2[p])
            )
        up.append(cur_up)
        mx.append(cur_mx)
        m2.append(cur_m2)
    return depth, up, mx, m2


def path_top2(
    u: int,
    v: int,
    depth: list[int],
    up: list[list[int]],
    mx: list[list[int]],
    m2: list[list[int]],
) -> tuple[int, int]:
    """求树上 u-v 路径的 (最大边权, 严格小于最大的次大边权)：两侧分别爬升、分段合并。"""
    a, b = u, v
    seg_u = (NEG, NEG)  # u 一侧已经爬过的路径段
    seg_v = (NEG, NEG)  # v 一侧已经爬过的路径段
    if depth[a] < depth[b]:
        a, b = b, a

    diff = depth[a] - depth[b]
    for k in range(LOG):
        if diff >> k & 1:  # 深度差的二进制位决定每一级跳不跳
            seg_u = merge_top2(seg_u, (mx[k][a], m2[k][a]))
            a = up[k][a]

    if a != b:  # 还没相遇，从高倍增位往下试，能分开跳就一起跳
        for k in range(LOG - 1, -1, -1):
            if up[k][a] != up[k][b]:
                seg_u = merge_top2(seg_u, (mx[k][a], m2[k][a]))
                seg_v = merge_top2(seg_v, (mx[k][b], m2[k][b]))
                a = up[k][a]
                b = up[k][b]
        # 此时两点的父节点就是 LCA，最后各爬一步把末段收进来
        seg_u = merge_top2(seg_u, (mx[0][a], m2[0][a]))
        seg_v = merge_top2(seg_v, (mx[0][b], m2[0][b]))
    return merge_top2(seg_u, seg_v)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    edges: list[tuple[int, int, int]] = []
    for _ in range(m):
        x, y, z = next(data), next(data), next(data)
        edges.append((z, x - 1, y - 1))  # 0-based 下标，按 (权值, 端点) 存，排序即 Kruskal 顺序

    mst_sum, g, light_edges = kruskal(edges, n)
    depth, up, mx, m2 = build_lifting(g)

    best = INF
    for a, b, w in light_edges:
        big, second = path_top2(a, b, depth, up, mx, m2)
        # 最小生成树最优 ⇒ 路径最大边权必 ≤ w；要让总权严格变大，只能删掉路径上严格小于 w 的最大边
        cut = big if big < w else second
        if cut >= 0:  # -1 表示整条路径都不小于 w，这次替换换不出更大的权值和
            best = min(best, mst_sum + w - cut)
    print(best)


if __name__ == "__main__":
    solve()
