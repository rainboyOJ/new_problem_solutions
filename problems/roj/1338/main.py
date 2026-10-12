#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 05:57
# update_at: 2026-10-12 14:53

# 二叉树结点的存储 + Floyd 全源最短路：
# 一个结点的三个字段聚合成 Node 对象：人口、左链接、右链接（0 表示无链接）。
# 如何使用：
# 1. 读入第 i 行：node[i].pop / lch / rch 赋值
# 2. 把链接当无向边写进距离矩阵 d（初始自己到自己 0，其余 INF）
# 3. Floyd 求出 d[u][v] 后枚举医院位置 u，取 sum(pop[v] * d[u][v]) 的最小值

import sys

INF = 10 ** 9  # 距离上界：边权为 1，实际距离远小于它


class Node:
    """编号 u 的结点：人口 + 左右链接（0 表示无链接）。"""

    def __init__(self) -> None:
        self.pop = 0  # 居民人口数
        self.lch = 0  # 左链接指向的结点编号，0 表示无链接
        self.rch = 0  # 右链接指向的结点编号，0 表示无链接


node: list[Node] = []    # node[u]：编号 u 的结点
d: list[list[int]] = []  # d[u][v]：u 到 v 的最少边数


def init(n: int) -> None:
    """造出 0..n 共 n+1 个结点，距离矩阵先设成"自己到自己 0，其余 INF"。"""
    global node, d
    node = [Node() for _ in range(n + 1)]
    d = [[0 if u == v else INF for v in range(n + 1)] for u in range(n + 1)]


def build_edges(n: int) -> None:
    """把结点里的左右链接翻译成无向边（相邻距离 1）：链接是双向可走的。"""
    for i in range(1, n + 1):
        for child in (node[i].lch, node[i].rch):
            if child:
                d[i][child] = d[child][i] = 1


def floyd(n: int) -> None:
    """Floyd 全源最短路：d[u][v] 是 u 到 v 的最少边数。"""
    for k in range(1, n + 1):
        d_k = d[k]                       # 缓存第 k 行，省掉内层重复索引
        for d_i in d[1:]:
            d_ik = d_i[k]
            for j in range(1, n + 1):
                if d_i[j] > d_ik + d_k[j]:
                    d_i[j] = d_ik + d_k[j]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    init(n)
    for i in range(1, n + 1):
        node[i].pop = next(data)
        node[i].lch = next(data)
        node[i].rch = next(data)

    build_edges(n)
    floyd(n)

    # 医院可以建在任意结点上，枚举每个候选 u 求"人口 x 距离"的总和，取最小
    print(min(sum(node[v].pop * d[u][v] for v in range(1, n + 1)) for u in range(1, n + 1)))


if __name__ == "__main__":
    solve()
