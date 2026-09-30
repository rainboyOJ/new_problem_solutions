#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-06 10:00
# update_at: 2026-07-06 10:00

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m, w = next(data), next(data), next(data)

    cost = [0] * (n + 1)   # 每朵云的价钱，下标 1..n
    value = [0] * (n + 1)  # 每朵云的价值
    for i in range(1, n + 1):
        cost[i], value[i] = next(data), next(data)

    parent = list(range(n + 1))  # 并查集：parent[i] = i 表示自己是根

    def find(x: int) -> int:
        """找 x 所在连通块的根（路径压缩）。"""
        while parent[x] != x:
            parent[x] = parent[parent[x]]  # 路径减半：爷爷直接当爸爸
            x = parent[x]
        return x

    for _ in range(m):
        u, v = next(data), next(data)
        ru, rv = find(u), find(v)
        if ru != rv:
            parent[ru] = rv  # 合并搭配关系：买 u 必买 v，反之亦然

    # 同一连通块捆绑成一件"套餐"：价钱与价值分别求和
    group_cost: dict[int, int] = {}
    group_value: dict[int, int] = {}
    for i in range(1, n + 1):
        root = find(i)
        group_cost[root] = group_cost.get(root, 0) + cost[i]
        group_value[root] = group_value.get(root, 0) + value[i]

    # 分组背包（这里每组只有一个套餐，即普通 0/1 背包），dp[j] = 花不超过 j 能得的最大价值
    dp = [0] * (w + 1)
    for root, c in group_cost.items():
        if c > w:  # 整组买不起，跳过
            continue
        d = group_value[root]
        for j in range(w, c - 1, -1):  # 倒序扫保证每件只买一次
            better = dp[j - c] + d > dp[j]
            if better:
                dp[j] = dp[j - c] + d

    print(dp[w])


if __name__ == "__main__":
    solve()
