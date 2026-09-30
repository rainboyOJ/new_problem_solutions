#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys


def solve() -> None:
    tokens = sys.stdin.read().split()
    if not tokens:
        return
    it = iter(tokens)
    n = int(next(it))
    m = int(next(it))

    # 扩展并查集：1..n 为自身（朋友域），n+1..2n 为敌人域（对立域）
    parent = list(range(2 * n + 1))

    def find(x: int) -> int:
        """带路径压缩的查根函数。"""
        root = x
        while parent[root] != root:
            root = parent[root]
        curr = x
        while curr != root:
            parent[curr], curr = root, parent[curr]
        return root

    def union(x: int, y: int) -> None:
        """合并两个节点所在的连通分量。"""
        rx, ry = find(x), find(y)
        if rx != ry:
            parent[rx] = ry

    for _ in range(m):
        opt = int(next(it))
        x = int(next(it))
        y = int(next(it))
        if opt == 0:
            union(x, y)
        else:
            # 敌人的敌人是朋友：x 的敌人与 y 合并，y 的敌人与 x 合并
            union(x, y + n)
            union(y, x + n)

    # 统计 1..n 中不同集合代表元的数量即为最大团伙数
    ans = len({find(i) for i in range(1, n + 1)})
    print(ans)


if __name__ == "__main__":
    solve()
