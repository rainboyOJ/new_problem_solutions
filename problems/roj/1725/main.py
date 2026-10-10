#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 18:56
# update_at: 2026-10-07 18:56

import sys
from collections.abc import Iterator

# 结点 0..n 表示前缀和 s[0..n]（s[0] = 0）。并查集里用「势」记录差：
# pot[i] = s[i] - s[parent[i]]，含义只在这里解释一次，合并时靠它把两棵树的
# 差值对齐，从而维护每条信息 s[y] - s[x-1] = w。


def find(x: int, parent: list[int], pot: list[int]) -> int:
    """返回 x 所在集合的根，并沿路压缩，使 pot[x] = s[x] - s[根]。"""
    root = x
    total = 0                       # 沿路径累计的势，就是 s[x] - s[根]
    while parent[root] != root:
        total += pot[root]
        root = parent[root]
    cur, acc = x, total
    while parent[cur] != cur:       # 第二趟：沿途结点直接挂到根上，势一并压平
        nxt, step = parent[cur], pot[cur]
        parent[cur], pot[cur] = root, acc
        acc -= step
        cur = nxt
    return root


def unite(a: int, b: int, w: int, parent: list[int], pot: list[int]) -> bool:
    """声明 s[b] - s[a] = w；返回 False 表示与已有信息矛盾。"""
    ra, rb = find(a, parent, pot), find(b, parent, pot)
    pa, pb = pot[a], pot[b]         # 压缩之后 pot[x] = s[x] - s[根]
    if ra == rb:
        return pb - pa == w         # 同一集合：已有的差必须正好是 w
    parent[rb] = ra
    pot[rb] = pa + w - pb           # 对齐两棵树的势，让 s[b] - s[a] = w 成立
    return True


def judge_group(n: int, m: int, data: Iterator[int]) -> bool:
    """读入并合并这一组的 m 条信息，返回账本是否可能为真。"""
    parent = list(range(n + 1))    # 结点 0..n 即前缀和 s[0..n]
    pot = [0] * (n + 1)            # 初始各自成根，势全 0

    consistent = True
    for _ in range(m):
        x, y, w = next(data), next(data), next(data)
        # 第 x..y 月的总收入 = s[y] - s[x-1]，逐条并入并查集
        consistent = consistent and unite(x - 1, y, w, parent, pot)
    return consistent


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)

    for _ in range(T):
        n, m = next(data), next(data)
        out.append("true" if judge_group(n, m, data) else "false")

    print("\n".join(out))


if __name__ == "__main__":
    solve()
