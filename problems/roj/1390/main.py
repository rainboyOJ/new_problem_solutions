#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 08:10
# update_at: 2026-09-30 08:10

import sys

# parent[x]：x 的父亲；rel[x]：x 到父亲的偏移（0 同类，1 吃父亲，2 被父亲吃）
# 关系在模 3 意义下闭合：同类=0，x 吃 y 记为 (rel 链差) = 1

def find(parent: list[int], rel: list[int], x: int) -> tuple[int, int]:
    """路径压缩版查找：返回 x 的根，以及 x 相对根的关系（模 3）。"""
    path = []
    while parent[x] != x:                  # 第一遍：收集 x 到根路径上的所有点
        path.append(x)
        x = parent[x]
    root = x
    r = 0
    for node in reversed(path):            # 第二遍：从根往下算偏移并压缩
        r = (r + rel[node]) % 3            # node 到根 = node 到父亲 + 父亲到根
        parent[node] = root
        rel[node] = r
    return root, r                         # r 此刻正是最外层 x（路径起点）到根的偏移


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    n, k = int(data[0]), int(data[1])

    parent = list(range(n + 1))            # 一开始每个动物自成一个集合
    rel = [0] * (n + 1)                    # 自己到自己当然是同类
    lies = 0
    idx = 2
    for _ in range(k):
        d, x, y = int(data[idx]), int(data[idx + 1]), int(data[idx + 2])
        idx += 3
        out_of_range = x > n or y > n
        self_eaten = d == 2 and x == y
        if out_of_range or self_eaten:
            lies += 1
            continue
        rx, rxy_x = find(parent, rel, x)   # rxy_x：x 相对根的关系
        ry, rxy_y = find(parent, rel, y)
        if rx != ry:                        # 两棵树尚未连通，本句必为真，用来合并
            # 需满足 (x 相对新根) = (y 相对新根) + w，即 w = d-1 + rxy_y - rxy_x
            w = (d - 1 + rxy_y - rxy_x) % 3
            parent[rx] = ry
            rel[rx] = w
        else:
            # 已同根：真实关系差 = (x 相对根) - (y 相对根)
            truth = (rxy_x - rxy_y) % 3
            if truth != d - 1:              # d-1：同类=0，x 吃 y=1
                lies += 1

    print(lies)


if __name__ == "__main__":
    solve()
