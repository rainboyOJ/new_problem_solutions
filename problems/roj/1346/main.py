#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 06:22
# update_at: 2026-09-30 06:33

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
    data = sys.stdin.buffer.read().split()
    if not data:  # 空输入直接退出，避免后面取下标越界
        return
    n, m = int(data[0]), int(data[1])
    parent = list(range(n + 1))  # 初始各自成块：parent[x] == x 表示 x 是代表元
    size = [1] * (n + 1)  # 块的大小，只在代表元（根）上有意义

    pos = 2
    for _ in range(m):
        union(parent, size, int(data[pos]), int(data[pos + 1]))
        pos += 2

    q = int(data[pos])
    pos += 1
    out: list[str] = []
    for _ in range(q):  # 代表元相同即为亲戚
        same = find(parent, int(data[pos])) == find(parent, int(data[pos + 1]))
        out.append("Yes" if same else "No")
        pos += 2
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
