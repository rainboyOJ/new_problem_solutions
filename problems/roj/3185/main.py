#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 23:58
# update_at: 2026-10-02 00:03

import sys


def find(parent: list[int], x: int) -> int:
    """路径减半地找 x 所在并查集的根，顺带把沿途节点挂向祖父。"""
    while parent[x] != x:
        parent[x] = parent[parent[x]]
        x = parent[x]
    return x


def minimum_added_weight(n: int, tree_edges: list[tuple[int, int, int]]) -> int:
    """补成完全图且原树仍是唯一 MST 时，新加边权和的最小值。

    按 Kruskal 的顺序（权值递增）接受树边：轮到权值 w 的边 (x,y) 时，两端点所在的
    连通块 A、B 内部的边已经被全部定好，此刻两个块之间唯一确定还存在的是这条树边。
    要让原树保持唯一 MST，A×B 里其余 |A|·|B|-1 条边的最小可行权值就是 w+1：
    取 w 会让它们与该树边并列（MST 不唯一），取更小则原树不再是 MST。
    """
    parent = list(range(n + 1))
    size = [1] * (n + 1)                       # 只有根节点的 size 有意义
    total = 0
    for weight, x, y in sorted(tree_edges):
        root_x, root_y = find(parent, x), find(parent, y)
        # 这两块之间除这条树边外的点对，路径最大树边权都是 weight，所以每条填 weight+1
        added = (size[root_x] * size[root_y] - 1) * (weight + 1)
        total += added
        if size[root_x] < size[root_y]:        # 按大小合并，控制树的深度
            root_x, root_y = root_y, root_x
        parent[root_y] = root_x
        size[root_x] += size[root_y]
    return total


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    test_count = next(data)

    for _ in range(test_count):
        n = next(data)
        tree_edges: list[tuple[int, int, int]] = []
        for _ in range(n - 1):
            x, y, weight = next(data), next(data), next(data)
            tree_edges.append((weight, x, y))  # 权值放首位，交给 sorted 排 Kruskal 序
        out.append(str(minimum_added_weight(n, tree_edges)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
