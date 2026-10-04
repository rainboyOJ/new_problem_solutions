#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 14:27
# update_at: 2026-09-30 14:27

import sys
from itertools import combinations

MOD = 31011


def find(parent: list[int], u: int) -> int:
    """查带路径压缩的并查集代表元。"""
    while parent[u] != u:
        parent[u] = parent[parent[u]]
        u = parent[u]
    return u


def count_valid_subsets(edges: list[tuple[int, int]], need: int, base_parent: list[int]) -> int:
    """在同权边集中暴力选择 need 条边，统计能形成无环森林的方案数。"""
    if need == 0:
        return 1

    valid_count = 0
    for chosen in combinations(edges, need):
        parent = list(base_parent)
        cycle_found = False
        for u, v in chosen:
            ru = find(parent, u)
            rv = find(parent, v)
            if ru == rv:
                cycle_found = True
                break
            parent[ru] = rv
        if not cycle_found:
            valid_count += 1
    return valid_count


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    tokens = list(data)
    if not tokens:
        return
    it = iter(tokens)
    n = next(it)
    m = next(it)

    raw_edges = [(next(it), next(it), next(it)) for _ in range(m)]
    raw_edges.sort(key=lambda e: e[2])

    # 第一阶段：Kruskal 探测各权值段在生成树中必须贡献的边数
    parent = list(range(n + 1))
    groups: list[tuple[list[tuple[int, int]], int]] = []  # (当前权值的边集, 需选取的边数)
    total_edges = 0

    idx = 0
    while idx < m:
        weight = raw_edges[idx][2]
        group_edges: list[tuple[int, int]] = []
        chosen_in_group = 0

        while idx < m and raw_edges[idx][2] == weight:
            u, v, _ = raw_edges[idx]
            group_edges.append((u, v))
            ru = find(parent, u)
            rv = find(parent, v)
            if ru != rv:
                parent[ru] = rv
                chosen_in_group += 1
                total_edges += 1
            idx += 1

        if chosen_in_group > 0:
            groups.append((group_edges, chosen_in_group))

    # 图不连通无法构成最小生成树
    if total_edges < n - 1:
        print(0)
        return

    # 第二阶段：按权值段独立统计选取方案数并累乘
    work_parent = list(range(n + 1))
    ans = 1

    for edges, need in groups:
        # 将边端点映射为当前连通分量代表元
        mapped_edges = [(find(work_parent, u), find(work_parent, v)) for u, v in edges]
        filtered_edges = [(u, v) for u, v in mapped_edges if u != v]

        ways = count_valid_subsets(filtered_edges, need, work_parent)
        ans = (ans * ways) % MOD

        # 将该权值段在并查集中真实合并（任意一种无环选取方案产生的连通性一致）
        for u, v in edges:
            ru = find(work_parent, u)
            rv = find(work_parent, v)
            if ru != rv:
                work_parent[ru] = rv

    print(ans)


if __name__ == "__main__":
    solve()
