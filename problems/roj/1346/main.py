#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 06:22
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


def main() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data, None)  # 首 token 是人数；空输入按原样直接返回
    if n is None:
        return
    m = next(data)     # 关系条数
    dsu = DSU(n)       # 初始各自成块

    for _ in range(m):
        a, b = next(data), next(data)  # 一条关系连接 a、b
        dsu.unite(a, b)

    q = next(data)  # 询问次数
    out: list[str] = []
    for _ in range(q):  # 代表元相同即为亲戚
        c, d = next(data), next(data)
        out.append("Yes" if dsu.same(c, d) else "No")
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
