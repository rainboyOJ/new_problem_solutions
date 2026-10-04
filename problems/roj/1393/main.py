#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:50
# update_at: 2026-07-05 21:50

import sys

data = iter(map(int, sys.stdin.buffer.read().split()))
n, m = next(data), next(data)

father = list(range(n + 1))  # 并查集父指针，0 号下标不占


def find(x: int) -> int:
    """找 x 的代表元，顺手路径压缩。"""
    root = x
    while father[root] != root:
        root = father[root]
    while father[x] != root:  # 第二遍把路径上的点全部挂到 root
        father[x], x = root, father[x]
    return root


# 第一遍：必选渠道全部累加费用并合并连通块
total = 0
optional: list[tuple[int, int, int]] = []  # (w, u, v) 可选渠道
for _ in range(m):
    p, u, v, w = next(data), next(data), next(data), next(data)
    if p == 1:
        total += w  # 同一对 u,v 的多条必选渠道全部要选，费用累加
        father[find(u)] = find(v)
    else:
        optional.append((w, u, v))

# 第二遍：对可选渠道按费用做 Kruskal，补齐连通块
for w, u, v in sorted(optional):
    ru, rv = find(u), find(v)
    if ru != rv:
        total += w
        father[ru] = rv

print(total)
