#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 08:29
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
    """M a b 合并两个家族，Q a 输出 a 所在家族的人数。"""
    # token 里整数与操作符 M/Q 混排，没法整体 map(int)，按位置顺序消费、用到时再转 int
    data = iter(sys.stdin.buffer.read().split())
    n, m = int(next(data)), int(next(data))
    dsu = DSU(n)  # sz 只在根上有效，取人数要先 find 到根

    out: list[str] = []
    for _ in range(m):
        op = next(data)  # 操作符 token：b"M" 合并 / b"Q" 查询
        if op == b"M":
            a, b = int(next(data)), int(next(data))
            dsu.unite(a, b)  # 按大小合并，小家族整棵挂到大家族的根下
        elif op == b"Q":
            a = int(next(data))
            out.append(str(dsu.sz[dsu.find(a)]))

    print("\n".join(out))


if __name__ == "__main__":
    solve()
