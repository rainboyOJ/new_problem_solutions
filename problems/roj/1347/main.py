#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 06:23
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
    data = iter(sys.stdin.buffer.read().split())
    n, m = int(next(data)), int(next(data))

    width = n + 1                        # 真实数据有越界边（x=n 向下 / y=n 向右）
    dsu = DSU(width * width)             # 点 (x, y) 编号 (x-1)*width + y
    step = {b"D": width, b"R": 1}        # D 是向下走一行，R 是向右走一格

    for i in range(1, m + 1):
        x, y = int(next(data)), int(next(data))
        u = (x - 1) * width + y
        v = u + step[next(data)]

        if not dsu.unite(u, v):          # 两端已连通，加这条边就成环，它就是封圈那一步
            print(i)
            return

    print("draw")


if __name__ == "__main__":
    solve()
