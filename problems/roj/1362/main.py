#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 07:05
# update_at: 2026-10-04 13:21

import sys
from collections import defaultdict


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data, None)
    if n is None:                                        # 空输入：直接返回
        return
    k = next(data)
    edges = [(next(data), next(data)) for _ in range(k)]  # 每次顺序消费一对关系 (α, β)

    parent = list(range(n + 1))                          # 并查集：每个人的代表元

    def find(x: int) -> int:
        """带路径压缩查找 x 所在集合的代表元。"""
        while parent[x] != x:
            parent[x] = parent[parent[x]]                  # 路径减半
            x = parent[x]
        return x

    def union(x: int, y: int) -> None:
        """把 x、y 所在家庭合并。"""
        rx, ry = find(x), find(y)
        if rx != ry:
            parent[ry] = rx

    for x, y in edges:
        union(x, y)

    size = defaultdict(int)                              # 每个家庭代表元 → 人数
    for i in range(1, n + 1):
        size[find(i)] += 1

    families = len(size)                                 # 家庭总数
    largest = max(size.values()) if size else 0          # 最大家庭人数
    print(f"{families} {largest}")


if __name__ == "__main__":
    solve()
