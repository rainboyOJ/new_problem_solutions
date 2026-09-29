#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 06:23
# update_at: 2026-09-30 06:23

import sys


def find(parent: list[int], x: int) -> int:
    """返回 x 所在连通块的根，并把路径上的点直接挂到根上（路径压缩）。"""
    root = x
    while parent[root] != root:          # 先沿父指针走到根
        root = parent[root]
    while parent[x] != root:             # 再把这一路上的点全部改指根
        parent[x], x = root, parent[x]
    return root


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n, m = int(next(data)), int(next(data))

    width = n + 1                        # 真实数据有越界边（x=n 向下 / y=n 向右）
    parent = list(range(width * width))
    step = {b"D": width, b"R": 1}        # 点 (x, y) 编号 (x-1)*width + (y-1)

    for i in range(1, m + 1):
        x, y = int(next(data)), int(next(data))
        u = (x - 1) * width + (y - 1)
        v = u + step[next(data)]

        root_u, root_v = find(parent, u), find(parent, v)
        if root_u == root_v:             # 两端已连通，加这条边就成环，它就是封圈那一步
            print(i)
            return
        parent[root_v] = root_u          # 否则合并两棵并查集树

    print("draw")


if __name__ == "__main__":
    solve()
