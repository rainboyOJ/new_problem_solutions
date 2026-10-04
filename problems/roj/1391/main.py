#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 08:20
# update_at: 2026-09-30 08:24

import sys
from collections.abc import Iterable


def mst_weight(n: int, edges: list[tuple[int, int, int]]) -> int:
    """返回最小生成树的边权和；图不连通时只算能连通部分的最小生成森林。"""
    parent = list(range(n + 1))  # 并查集：parent[x] == x 表示 x 还是一个集合的根

    def find(x: int) -> int:
        """返回 x 所在集合的根，顺手做路径压缩。"""
        while parent[x] != x:
            parent[x] = parent[parent[x]]  # 隔代压缩，写起来比递归浅
            x = parent[x]
        return x

    total = 0
    used = 0  # 已并入生成树的边数，等于 n-1 时整张图已经连通
    for w, u, v in sorted(edges):  # 元组排序先比 w，权重升序就是 Kruskal 的贪心顺序
        ru, rv = find(u), find(v)
        if ru == rv:
            continue  # 两端已经连通，这条边加上去正好成环，必须删掉
        parent[ru] = rv
        total += w
        used += 1
        if used == n - 1:
            break
    return total


def solve() -> None:
    data: Iterable[int] = map(int, sys.stdin.buffer.read().split())
    it = iter(data)
    n, k = next(it), next(it)
    edges = []
    total = 0
    for _ in range(k):
        i, j, m = next(it), next(it), next(it)
        edges.append((m, i, j))  # 权重放到第 0 位，Kruskal 直接按元组排序即可
        total += m
    keep = mst_weight(n, edges)
    print(total - keep)  # 总量固定，留下的越少被删掉的越多


if __name__ == "__main__":
    solve()
