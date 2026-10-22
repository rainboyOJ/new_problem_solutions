#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-21 10:20
# update_at: 2026-10-21 10:20
#
# P1550 [USACO08OCT] Watering Hole G
# 建模：加虚拟水源点 S（编号 n + 1），
#   S -- i   权 W_i    在第 i 块田打井 = 从水源接一条边到这块田
#   i -- j   权 P_ij   两块田之间铺一根水管
# 合法方案等价于 S 与全部田连通，于是答案就是这 n + 1 个点的最小生成树。
# P_ij = 0 是免费水管，是合法的 0 权边，必须保留；只跳过 i == j 的对角线自环。

import sys

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Edge = tuple[int, int, int]  # (起点 u, 终点 v, 边权 w)


def find(parent: list[int], x: int) -> int:
    """找 x 所在集合的根，顺路把路径上的点挂到根上（迭代压缩，不受递归深度限制）。"""
    root = x
    while parent[root] != root:
        root = parent[root]
    while parent[x] != root:
        parent[x], x = root, parent[x]
    return root


def kruskal(node_cnt: int, edges: list[Edge]) -> int | None:
    """返回最小生成树总权值，图不连通时返回 None；sorted 生成新列表，不打乱调用者的边表。"""
    parent = list(range(node_cnt + 1))  # parent[x]：x 的父节点，x 是根时等于 x
    size = [1] * (node_cnt + 1)         # size[x]：x 是根时该集合的点数

    total = selected = 0
    for u, v, w in sorted(edges, key=lambda edge: edge[2]):  # 边权小的先试
        root_u, root_v = find(parent, u), find(parent, v)
        if root_u == root_v:  # 两端已经连通，选它就会成环
            continue
        if size[root_u] < size[root_v]:  # 小集合接到大集合下面
            root_u, root_v = root_v, root_u
        parent[root_v] = root_u
        size[root_u] += size[root_v]
        total += w
        selected += 1
        if selected == node_cnt - 1:  # 生成树正好 node_cnt - 1 条边，选满就停
            break
    return total if selected == node_cnt - 1 else None


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    field_cnt = next(data)     # 田地数 n
    source = field_cnt + 1     # 虚拟水源点 S，表示"农场外面的那处水"

    edges: list[Edge] = []
    # S 到每块田：权 W_i，表示在这块田打井
    for i in range(1, field_cnt + 1):
        edges.append((source, i, next(data)))

    # 田与田之间：矩阵对称，只取上三角；P_ij = 0 是免费水管，要保留
    for i in range(1, field_cnt + 1):
        for j in range(1, field_cnt + 1):
            price = next(data)
            if i < j:
                edges.append((i, j, price))

    # 每块田都有一条到 S 的边，图必然连通，返回值不会为 None
    print(kruskal(source, edges))


if __name__ == "__main__":
    solve()
