#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-08-10 21:46
# update_at: 2026-10-21 14:50
#
# main.py：买礼物。每件礼物可花 A 元直接买；若已买 i，则买 j 只需 K[i][j] 元。求买齐全部的最小花费。
# 建模：加虚拟源点 S（编号 B+1）表示"从商店原价买"，于是
#   S -- j       权 A          直接买第 j 件
#   i -- j       权 K[i][j]    已买 i 后，用优惠价买 j
# 买齐全部 = 让 S 和所有礼物点连通，总花费 = 选中边的权和，所以是最小生成树。
# 最优解一定无环：有环就删掉环上任一条，连通性不变、代价不增，于是连通且无环即为树。
# 反向也成立：树连通，从 S 做 BFS 能到达所有礼物，按 BFS 序购买时父节点必已买好。
# 注意 K[i][j] = 0 表示"没有优惠"，必须当无边跳过，不能当 0 权边（否则会误以为能免费连锁）。
# 最小生成树直接调用 rbook 代码模板 mst-kruskal-py（见文章《最小生成树》）。

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


def kruskal(n: int, edges: list[Edge]) -> int | None:
    """返回 MST 总权值，图不连通时返回 None；sorted 生成新列表，不打乱调用者的边表。"""
    parent = list(range(n + 1))  # parent[x]：x 的父节点，x 是根时等于 x
    size = [1] * (n + 1)         # size[x]：x 是根时该集合的点数

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
        if selected == n - 1:  # 生成树正好 n - 1 条边，选满就停
            break
    return total if selected == n - 1 else None


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    direct_cost = next(data)  # 直接买任意一件礼物的价格 A
    gift_cnt = next(data)     # 礼物数量 B

    source = gift_cnt + 1  # 虚拟源点 S，表示"从商店原价买"
    edges: list[Edge] = []

    # S 到每件礼物：权 A，表示直接买
    for j in range(1, gift_cnt + 1):
        edges.append((source, j, direct_cost))

    # 礼物之间的优惠边：矩阵对称，只取上三角即可
    for i in range(1, gift_cnt + 1):
        for j in range(1, gift_cnt + 1):
            price = next(data)
            if i >= j:
                continue  # 对角线 K[i][i]=0 与下三角都跳过
            if price == 0:
                continue  # 0 表示没有优惠，当无边处理
            edges.append((i, j, price))

    # 所有礼物都有一条到 S 的边，图必然连通，返回值不会为 None
    print(kruskal(source, edges))


if __name__ == "__main__":
    solve()
