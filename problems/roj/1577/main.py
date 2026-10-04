#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 19:46
# update_at: 2026-09-30 19:46

import sys


def divisor_sum_table(n: int) -> list[int]:
    """筛法求 1..n 每个数的真约数和（不含自身）。"""
    s = [0] * (n + 1)
    for d in range(1, n // 2 + 1):
        for m in range(d * 2, n + 1, d):  # d 是 m 的真约数，逐个累加
            s[m] += d
    return s


def build_graph(n: int) -> list[list[int]]:
    """建无向图：真约数和 y < x 时连边 x—y，双向可变换。"""
    s = divisor_sum_table(n)
    adj: list[list[int]] = [[] for _ in range(n + 1)]
    for x in range(2, n + 1):
        y = s[x]
        if y < x:  # y == x（完全数）或 y > x 时本侧不建边；对侧若满足会由对侧建出
            adj[x].append(y)
            adj[y].append(x)
    return adj


def farthest(adj: list[list[int]], start: int) -> tuple[int, int, list[int]]:
    """从 start 分层扩散，返回 (最远点, 最远距离, 走过的所有点)。"""
    dist: dict[int, int] = {start: 0}
    layer = [start]
    far = start
    depth = 0
    while layer:
        nxt = [v for u in layer for v in adj[u] if v not in dist]
        if not nxt:
            break
        depth += 1
        for v in nxt:
            dist[v] = depth
        far = nxt[-1]  # 最后一层任意一点都可作为"最远点"
        layer = nxt
    return far, depth, list(dist)


def forest_diameter(adj: list[list[int]]) -> int:
    """森林求直径：每块先任取一点找最远点，再从它扩散，距离即该块直径。"""
    seen: set[int] = set()
    ans = 0
    for start in range(1, len(adj)):
        if start in seen:
            continue
        u, _, nodes = farthest(adj, start)   # 第一次：确定连通块一端 u，并标记整块
        seen.update(nodes)
        _, diameter, _ = farthest(adj, u)    # 第二次：u 出发的最远距离就是直径
        ans = max(ans, diameter)
    return ans


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    print(forest_diameter(build_graph(n)))


if __name__ == "__main__":
    solve()
