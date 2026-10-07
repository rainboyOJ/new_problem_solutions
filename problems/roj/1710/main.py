#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 17:32
# update_at: 2026-10-07 17:32

import sys


def root(parent: list[int], x: int) -> int:
    """并查集找根，带路径压缩（迭代写法，链深 1e5 也不爆栈）。"""
    while parent[x] != x:
        parent[x] = parent[parent[x]]
        x = parent[x]
    return x


def extra_weight(triples: list[tuple[int, int, int]], n: int) -> int:
    """Kruskal 式合并：每条树边 (u,v,w) 合并两块时，补 sx*sy-1 条权 w+1 的非树边。"""
    parent = list(range(n + 1))
    size = [1] * (n + 1)
    total = 0
    for w, u, v in sorted((w, u, v) for u, v, w in triples):  # 按权值升序，等价于 Kruskal
        a, b = root(parent, u), root(parent, v)
        # 跨两块 sx*sy 条点对里 1 条已是树边，其余取 w+1 恰好不破坏 MST 的唯一性
        total += (size[a] * size[b] - 1) * (w + 1)
        if size[a] < size[b]:  # 小树挂大树
            a, b = b, a
        parent[b] = a
        size[a] += size[b]
    return total


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    triples = [(next(data), next(data), next(data)) for _ in range(n - 1)]  # (u, v, w)
    print(sum(w for _, _, w in triples) + extra_weight(triples, n))  # 树边全额 + 补齐的非树边


if __name__ == "__main__":
    solve()
