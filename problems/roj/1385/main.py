#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
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
    tokens = sys.stdin.read().split()
    if not tokens:
        return
    it = iter(tokens)
    n = int(next(it))
    m = int(next(it))

    # 扩展并查集：1..n 为自身（朋友域），n+1..2n 为敌人域（对立域）
    dsu = DSU(2 * n)

    for _ in range(m):
        opt = int(next(it))
        x = int(next(it))
        y = int(next(it))
        if opt == 0:
            dsu.unite(x, y)
        else:
            # 敌人的敌人是朋友：x 的敌人与 y 合并，y 的敌人与 x 合并
            dsu.unite(x, y + n)
            dsu.unite(y, x + n)

    # 统计 1..n 中不同集合代表元的数量即为最大团伙数
    ans = len({dsu.find(i) for i in range(1, n + 1)})
    print(ans)


if __name__ == "__main__":
    solve()
