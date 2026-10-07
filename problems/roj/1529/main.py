#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 15:13
# update_at: 2026-10-07 15:13

import sys
from collections.abc import Iterator


def find_root(fa: list[int], x: int) -> int:
    """并查集找根，带路径压缩。"""
    while fa[x] != x:
        fa[x] = fa[fa[x]]
        x = fa[x]
    return x


def has_euler_circuit(n: int, m: int, data: Iterator[int]) -> bool:
    """读入一个样例的 m 条边，判断这张图是否存在欧拉回路。"""
    deg = [0] * (n + 1)      # deg[v] = 点 v 的度数；自环 (v,v) 给 v 记 2 度
    fa = list(range(n + 1))  # 并查集，只用来判断「有边的点」是否连成一片

    for _ in range(m):
        u, v = next(data), next(data)
        deg[u] += 1
        deg[v] += 1
        root_u, root_v = find_root(fa, u), find_root(fa, v)
        if root_u != root_v:
            fa[root_u] = root_v

    if any(d % 2 for d in deg[1:]):  # 条件一：所有点的度数都是偶数
        return False
    # 条件二：度数为正的顶点里并查集根只有一个；一条边都没有时 0 个，也算连通
    roots = {find_root(fa, v) for v in range(1, n + 1) if deg[v]}
    return len(roots) <= 1


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    for n in data:  # 每个样例的第一个数就是 N，读到 0 表示输入结束
        if n == 0:
            break
        m = next(data)
        out.append("1" if has_euler_circuit(n, m, data) else "0")
    print("\n".join(out))


if __name__ == "__main__":
    solve()
