#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 06:22
# update_at: 2026-10-04 11:42

import sys


def find(parent: list[int], x: int) -> int:
    """返回 x 所在连通块的代表元，返回前顺路把路径减半。"""
    while parent[x] != x:
        parent[x] = parent[parent[x]]  # 路径减半：每跳一步就把父指针提升一层
        x = parent[x]
    return x


def union(parent: list[int], size: list[int], a: int, b: int) -> None:
    """合并 a、b 所在的两个连通块；按 size 决定谁当根，避免树退化成长链。"""
    ra, rb = find(parent, a), find(parent, b)
    if ra == rb:  # 已在同一块：自环与重复关系都在这里被吸收
        return
    if size[ra] < size[rb]:  # 小树挂到大树上：任一结点的深度不超过 O(log n)
        ra, rb = rb, ra
    parent[rb] = ra
    size[ra] += size[rb]


def main() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data, None)  # 首 token 是人数；空输入按原样直接返回
    if n is None:
        return
    m = next(data)               # 关系条数
    parent = list(range(n + 1))  # 初始各自成块：parent[x] == x 表示 x 是代表元
    size = [1] * (n + 1)  # 块的大小，只在代表元（根）上有意义

    for _ in range(m):
        a, b = next(data), next(data)  # 一条关系连接 a、b
        union(parent, size, a, b)

    q = next(data)  # 询问次数
    out: list[str] = []
    for _ in range(q):  # 代表元相同即为亲戚
        c, d = next(data), next(data)
        same = find(parent, c) == find(parent, d)
        out.append("Yes" if same else "No")
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
