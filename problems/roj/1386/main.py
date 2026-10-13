#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 08:10
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
    n = next(data)

    # 团伙只可能和编号更大的团伙连通才影响"删掉 1..k"之后的答案，
    # 所以邻接表只保留大编号邻居，无向图的一半就够用。
    graph: list[list[int]] = [[] for _ in range(n + 1)]
    for i in range(1, n + 1):
        degree = next(data)
        graph[i] = [j for j in (next(data) for _ in range(degree)) if j > i]

    dsu = DSU(n)  # sz 只在根上有效：集团内的团伙数

    # 倒序加入：第 i 轮结束后集合 {i, i+1, ..., n} 的连通块，
    # 恰好等于"删掉 1..i-1 后剩下来的集团"。首次出现超过一半的集团时即答案。
    for i in range(n, 0, -1):
        for j in graph[i]:
            dsu.unite(i, j)
        # unite 按大小合并会换根，所以这里必须重新 find 一次拿合并后的根
        if dsu.sz[dsu.find(i)] > n // 2:
            print(i)
            return

    print(n)  # 整图连通时上面必然已经返回；这里兜住非连通输入，删光才算达标


if __name__ == "__main__":
    solve()
