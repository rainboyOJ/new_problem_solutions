#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 08:10
# update_at: 2026-09-30 08:12

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    # 团伙只可能和编号更大的团伙连通才影响"删掉 1..k"之后的答案，
    # 所以邻接表只保留大编号邻居，无向图的一半就够用。
    graph: list[list[int]] = [[] for _ in range(n + 1)]
    for i in range(1, n + 1):
        degree = next(data)
        graph[i] = [j for j in (next(data) for _ in range(degree)) if j > i]

    parent = list(range(n + 1))  # 并查集：parent[i] == i 表示 i 是所在集团的代表
    size = [1] * (n + 1)         # 只对代表有效：集团内的团伙数

    def find(x: int) -> int:
        """返回 x 所在集团的代表，顺路做路径压缩。"""
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

    # 倒序加入：第 i 轮结束后集合 {i, i+1, ..., n} 的连通块，
    # 恰好等于"删掉 1..i-1 后剩下来的集团"。首次出现超过一半的集团时即答案。
    for i in range(n, 0, -1):
        root = find(i)
        for j in graph[i]:
            other = find(j)
            if other != root:
                parent[other] = root
                size[root] += size[other]
        if size[root] > n // 2:
            print(i)
            return

    print(n)  # 整图连通时上面必然已经返回；这里兜住非连通输入，删光才算达标


if __name__ == "__main__":
    solve()
