#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 17:45
# update_at: 2026-10-07 17:45

import sys
from itertools import combinations
from math import hypot

# 完全图的一条边：欧氏距离 + 两个端点下标。整个算法只操作这种三元组。
type EdgeList = list[tuple[float, int, int]]


def find(fa: list[int], x: int) -> int:
    """并查集查根，迭代 + 隔代路径压缩（N 可达 1000，避免递归）。"""
    while fa[x] != x:
        fa[x] = fa[fa[x]]
        x = fa[x]
    return x


def build_tree(n: int, edges: EdgeList) -> tuple[float, EdgeList]:
    """Kruskal：升序扫边，返回最小生成树总权值 W 与构成它的 N-1 条边。"""
    fa = list(range(n))
    total = 0.0
    tree: EdgeList = []
    for w, u, v in edges:
        ru, rv = find(fa, u), find(fa, v)
        if ru == rv:
            continue                     # 两端已连通，这条边会成环
        fa[ru] = rv
        total += w
        tree.append((w, u, v))
        if len(tree) == n - 1:
            break                        # 生成树已满，后面的边用不上
    return total, tree


def max_pleasure(tree: EdgeList, total: float, p: list[int]) -> float:
    """按树边升序合并分量，求愉悦度 A/B 的最大值。

    升序合并到边 e 时，跨越当前两个分量的所有点对，其在 MST 上的路径最大边
    恰为 w(e)，于是 B 的最小值 = W - w(e)；这些点对里 A 最大的就是
    两个分量各自最大的 P 之和。
    """
    fa = list(range(len(p)))
    best = list(p)                       # best[根] = 所在分量内最大的美味度 P
    ans = 0.0
    for w, u, v in tree:
        a, b = find(fa, u), find(fa, v)
        ratio = (best[a] + best[b]) / (total - w)
        if ratio > ans:
            ans = ratio
        merged = best[a] if best[a] > best[b] else best[b]
        fa[a] = b
        best[b] = merged
    return ans


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    pts: list[tuple[int, int, int]] = []
    for _ in range(n):
        x, y, q = next(data), next(data), next(data)   # 题面的 x、y、P
        pts.append((x, y, q))

    # 完全图：每个点对一条边，权值取欧氏距离（排序后即为 Kruskal 的扫描顺序）
    edges: EdgeList = sorted(
        (hypot(pts[i][0] - pts[j][0], pts[i][1] - pts[j][1]), i, j)
        for i, j in combinations(range(n), 2)
    )
    p = [q for _, _, q in pts]           # 每家的美味度 P，下标与点编号一致

    total, tree = build_tree(n, edges)
    print(f"{max_pleasure(tree, total, p):.2f}")


if __name__ == "__main__":
    solve()
