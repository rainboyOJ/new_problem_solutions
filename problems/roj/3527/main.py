#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 06:19
# update_at: 2026-10-02 06:19

import sys
from collections.abc import Iterator
from functools import cache


def bits(mask: int) -> Iterator[int]:
    """依次产出位图 mask 中为 1 的节点下标。"""
    while mask:
        low = mask & -mask
        yield low.bit_length() - 1
        mask ^= low


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    p = next(data)  # 题面的 p：传播途径（边）条数，本题保证是一棵树
    adj: list[list[int]] = [[] for _ in range(n)]
    for _ in range(p):
        a, b = next(data) - 1, next(data) - 1
        adj[a].append(b)
        adj[b].append(a)

    # 以 0 号点（患者 1）为根：边遍历边追加，order 即层序，父一定先于子出现
    parent = [-1] * n
    order = [0]
    for u in order:
        for v in adj[u]:
            if v and parent[v] < 0:  # 根 0 的 parent 永远是 -1，用 v 本身排除
                parent[v] = u
                order.append(v)

    children: list[list[int]] = [[] for _ in range(n)]
    for v in range(1, n):
        children[parent[v]].append(v)

    size = [1] * n  # 以 u 为根的子树人数（含 u 自己）
    for u in reversed(order):
        for v in children[u]:
            size[u] += size[v]

    kids = [sum(1 << v for v in children[u]) for u in range(n)]  # 各点孩子的位图

    @cache
    def saved(frontier: int) -> int:
        """本层可切断候选（位图 frontier）下，之后每层各切一条边最多能保住的人数。"""
        if not frontier:
            return 0
        # 本层除被切断点外其余候选全部感染，下一层候选 = 这些点的孩子
        nxt = 0
        for u in bits(frontier):
            nxt |= kids[u]
        # 每层必切一条：切断 u 保住整棵子树；不切时 u 子树内未来收益至多 size[u]-1
        return max(size[u] + saved(nxt & ~kids[u]) for u in bits(frontier))

    # 最终感染数 = 总人数 - 各层切断子树保住的人数（初始候选是根的孩子）
    print(n - saved(kids[0]))


if __name__ == "__main__":
    solve()
