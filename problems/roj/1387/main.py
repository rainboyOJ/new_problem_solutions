#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-06 10:00
# update_at: 2026-10-13 22:28

import sys


class DSU:
    """并查集 (Disjoint Set Union)"""

    def __init__(self, n: int):
        # 1-indexed, fa 初始指向自己，sz 初始为 1
        self.fa = list(range(n + 1))
        self.sz = [1] * (n + 1)

    def find(self, x: int) -> int:
        """查找根节点，两趟路径压缩：先走到根，再把整条路径挂到根上"""
        root = x
        while self.fa[root] != root:
            root = self.fa[root]
        while self.fa[x] != root:
            self.fa[x], x = root, self.fa[x]
        return root

    def same(self, x: int, y: int) -> bool:
        """判断 x 和 y 是否属于同一个集合"""
        return self.find(x) == self.find(y)

    def unite(self, x: int, y: int) -> bool:
        """按大小合并两个集合 (小树挂大树)；已在同一集合返回 False"""
        fx, fy = self.find(x), self.find(y)
        if fx == fy:
            return False
        if self.sz[fx] < self.sz[fy]:
            fx, fy = fy, fx
        self.fa[fy] = fx
        self.sz[fx] += self.sz[fy]
        return True


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m, w = next(data), next(data), next(data)

    cost = [0] * (n + 1)   # 每朵云的价钱，下标 1..n
    value = [0] * (n + 1)  # 每朵云的价值
    for i in range(1, n + 1):
        cost[i], value[i] = next(data), next(data)

    dsu = DSU(n)

    for _ in range(m):
        u, v = next(data), next(data)
        dsu.unite(u, v)  # 合并搭配关系：买 u 必买 v，反之亦然

    # 同一连通块捆绑成一件"套餐"：价钱与价值分别按根累加
    group_cost = [0] * (n + 1)
    group_value = [0] * (n + 1)
    for i in range(1, n + 1):
        root = dsu.find(i)
        group_cost[root] += cost[i]
        group_value[root] += value[i]

    # 分组背包（这里每组只有一个套餐，即普通 0/1 背包），dp[j] = 花不超过 j 能得的最大价值
    dp = [0] * (w + 1)
    for root in range(1, n + 1):
        c = group_cost[root]
        if c == 0 or c > w:  # 不是有货的根，或整组买不起，跳过
            continue
        d = group_value[root]
        for j in range(w, c - 1, -1):  # 倒序扫保证每件只买一次
            better = dp[j - c] + d > dp[j]
            if better:
                dp[j] = dp[j - c] + d

    print(dp[w])


if __name__ == "__main__":
    solve()
