#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 14:18
# update_at: 2026-09-30 14:18

import sys


def find(root: list[int], x: int) -> int:
    """并查集查根：路径压缩后返回 x 所在连通块的代表点。"""
    while root[x] != x:
        root[x] = root[root[x]]
        x = root[x]
    return x


def pair_max_edge_sum(n: int, edges: list[tuple[int, int, int]]) -> int:
    """按边权升序合并连通块，求所有点对之间树上路径的最大边权之和。

    合并时跨两块的点对路径必经过当前边，且块内边权都不超过它，
    所以这批点对的"路径最大边权"恰为这条边的权值。
    """
    root = list(range(n + 1))  # 父点表，下标 0 不用（点编号从 1 开始）
    size = [1] * (n + 1)
    total = 0
    for u, v, w in edges:
        ru, rv = find(root, u), find(root, v)
        total += w * size[ru] * size[rv]  # 跨块点对数 = 两块大小之积
        root[ru] = rv
        size[rv] += size[ru]
    return total


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    edges = [(next(data), next(data), next(data)) for _ in range(n - 1)]  # 依次读入 u、v、w
    edges.sort(key=lambda e: e[2])  # 按边权升序，即 Kruskal 的合并顺序

    # 全部点对的路径最大边权之和（树边已按原权计入），再给每个非树点对补 +1
    ans = pair_max_edge_sum(n, edges) + n * (n - 1) // 2 - (n - 1)
    print(ans)


if __name__ == "__main__":
    solve()
