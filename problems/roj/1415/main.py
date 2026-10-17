#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-17 23:10
# update_at: 2026-10-17 23:10
#
# 矩形加点求和：二维差分 + 二维树状数组（rbook_nunjucks 代码模板风格）。
# 和前置题 1416（静态覆盖计数）的关系：1416 沿 x 做扫描线把一维消掉，
# y 用差分 + 一维树状数组；本题加矩形和查询交替，x 无法提前扫完，
# 于是把「差分 + 前缀和」整体升到二维：
#   矩形 [l,r) x [d,u) 加 w  <=>  D(l,d)+=w, D(l,u)-=w, D(r,d)-=w, D(r,u)+=w
#   点 (x,y) 的答案        <=>  sum_{x'<=x, y'<=y} D(x',y')
# 单点加/前缀和都用外层 x、内层 y 的树状数组，单次 O(log^2)。
# 一旦某个矩形已被加入，它就一直有效，所以离线把所有端点收集起来离散化即可。

import sys
from bisect import bisect_left, bisect_right

type Seq = list[int]  # 1 下标 int 序列，下标 0 占位不用


class Fenwick2D:
    """二维树状数组：x、y 都离散化，外层 x 每个节点各带一个内层 y 的树状数组。"""

    def __init__(self, xs: Seq, points: list[tuple[int, int]]) -> None:
        # xs 是 1 下标升序去重表；points 是全部会出现的 (x, y)
        self.nx = len(xs) - 1
        self.xs = xs
        # col[i]：外层节点 i 需要的内层 y 坐标（升序去重），bit[i] 与之等长 +1
        col: list[list[int]] = [[] for _ in range(self.nx + 1)]
        for x, y in points:
            i = self.x_rank(x)
            while i <= self.nx:
                col[i].append(y)
                i += i & -i
        for i in range(1, self.nx + 1):
            col[i] = sorted(set(col[i]))
        self.col = col
        self.tree: list[Seq] = [[0] * (len(col[i]) + 1) for i in range(self.nx + 1)]

    def x_rank(self, x: int) -> int:
        """x 的 1 起名次；调用方保证 x 在离散化表里。"""
        return bisect_left(self.xs, x, 1)  # xs 是 1 下标，bisect 结果天然是名次

    def add(self, x: int, y: int, value: int) -> None:
        """二维单点加：原矩阵的 (x, y) 处 += value。"""
        i = self.x_rank(x)
        while i <= self.nx:
            tree = self.tree[i]
            j = bisect_left(self.col[i], y) + 1  # 内层 1 起名次
            m = len(self.col[i])
            while j <= m:
                tree[j] += value
                j += j & -j
            i += i & -i

    def prefix_sum(self, x: int, y: int) -> int:
        """二维前缀和：x' <= x 且 y' <= y 的所有点之和。"""
        total = 0
        i = self.x_rank(x)
        while i > 0:
            tree = self.tree[i]
            j = bisect_right(self.col[i], y)  # <= y 的内层坐标个数
            while j > 0:
                total += tree[j]
                j -= j & -j
            i -= i & -i
        return total


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    pos = 0
    n = data[pos]
    q = data[pos + 1]
    pos += 2

    # 统一成操作序列：op = (type, l, d, r, u, w) 或 (1, x, y, 0, 0, 0)
    ops: list[tuple[int, int, int, int, int, int]] = []
    for _ in range(n):
        l, d, r, u, w = data[pos:pos + 5]
        pos += 5
        ops.append((0, l, d, r, u, w))
    for _ in range(q):
        t = data[pos]
        pos += 1
        if t == 0:
            l, d, r, u, w = data[pos:pos + 5]
            pos += 5
            ops.append((0, l, d, r, u, w))
        else:
            x, y = data[pos:pos + 2]
            pos += 2
            ops.append((1, x, y, 0, 0, 0))

    # 收集所有会落进树状数组的坐标：矩形的 4 个差分角 + 询问点
    xs: Seq = [0]
    points: list[tuple[int, int]] = []
    for t, l, d, r, u, w in ops:
        if t == 0:
            for x, y in ((l, d), (l, u), (r, d), (r, u)):
                xs.append(x)
                points.append((x, y))
        else:
            xs.append(l)
            points.append((l, d))

    xs = [0] + sorted(set(xs[1:]))  # 1 下标升序去重
    bit = Fenwick2D(xs, points)

    out: list[str] = []
    for t, l, d, r, u, w in ops:
        if t == 0:
            # 二维差分：矩形加 = 4 个带符号的单点加
            bit.add(l, d, w)
            bit.add(l, u, -w)
            bit.add(r, d, -w)
            bit.add(r, u, w)
        else:
            out.append(str(bit.prefix_sum(l, d)))  # 查询点存的是 (x, y) = (l, d)

    sys.stdout.write("\n".join(out) + ("\n" if out else ""))


if __name__ == "__main__":
    solve()
