#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-04-18 10:00
# update_at: 2026-04-18 10:00

import sys


def find_root(parent: list[int], x: int) -> int:
    """查询节点 x 所在集合的代表元，带路径压缩。"""
    curr = x
    while parent[curr] != curr:
        curr = parent[curr]
    while parent[x] != curr:
        parent[x], x = curr, parent[x]
    return curr


def try_union(parent: list[int], u: int, v: int) -> bool:
    """若 u 和 v 尚未连通则合并并返回 True，否则返回 False。"""
    root_u, root_v = find_root(parent, u), find_root(parent, v)
    if root_u == root_v:
        return False
    parent[root_v] = root_u
    return True


def solve() -> None:
    tokens = sys.stdin.buffer.read().split()
    if not tokens:
        return
    data = iter(map(int, tokens))
    m, n = next(data), next(data)

    parent = list(range(m * n))

    # 预连接已存在的无费用边
    for x1 in data:
        y1, x2, y2 = next(data), next(data), next(data)
        u = (x1 - 1) * n + (y1 - 1)
        v = (x2 - 1) * n + (y2 - 1)
        try_union(parent, u, v)

    # 优先贪心选择花费为 1 的所有纵向边
    vertical_cost = sum(
        1
        for c in range(n)
        for r in range(m - 1)
        if try_union(parent, r * n + c, (r + 1) * n + c)
    )

    # 再贪心选择花费为 2 的所有横向边
    horizontal_cost = sum(
        2
        for r in range(m)
        for c in range(n - 1)
        if try_union(parent, r * n + c, r * n + c + 1)
    )

    print(vertical_cost + horizontal_cost)


if __name__ == "__main__":
    solve()
