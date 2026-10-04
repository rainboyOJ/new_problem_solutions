#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-28 17:05
# update_at: 2026-09-28 17:05

import sys


def quick_sort(edges: list[tuple[int, int, int]], left: int, right: int) -> None:
    """手写快速排序（挖坑法）。

    本题正确解只要求"任意最小生成树"，但官方数据由本题 std 的手写快排生成，
    同权边大量存在，快排的不稳定交换决定了选边顺序。要复现官方输出，
    排序必须与 std.cpp 完全同构，故不用 sorted()。
    """
    i, j = left, right
    pivot = edges[(left + right) // 2][2]            # 轴枢取中点元素的权
    while i <= j:
        while edges[i][2] < pivot:
            i += 1
        while edges[j][2] > pivot:
            j -= 1
        if i <= j:
            edges[i], edges[j] = edges[j], edges[i]  # 相等权也交换，不稳定性的来源
            i += 1
            j -= 1
    if i < right:
        quick_sort(edges, i, right)
    if left < j:
        quick_sort(edges, left, j)


def find(father: list[int], x: int) -> int:
    """路径压缩的并查集查找。"""
    if father[x] == x:
        return x
    father[x] = find(father, father[x])
    return father[x]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, e = next(data), next(data)                    # 城市数 n，边数 e

    # 读入无向边，小端点归一化在前；下标从 1 起，与快排的 [1, m] 区间对齐
    edges: list[tuple[int, int, int]] = [None] * (e + 1)  # (u, v, w)，0 号位空置
    for i in range(1, e + 1):
        u, v, w = next(data), next(data), next(data)
        if u > v:
            u, v = v, u
        edges[i] = (u, v, w)

    quick_sort(edges, 1, e)

    father = list(range(n + 1))                      # 城市编号 1..n，0 号位空置
    mst: list[tuple[int, int]] = []
    for i in range(1, e + 1):                        # 权从小到大尝试每条边
        u, v, _ = edges[i]
        ru, rv = find(father, u), find(father, v)
        if ru != rv:                                 # 不在同一连通块 → 选中
            father[ru] = rv
            mst.append((u, v))
            if len(mst) == n - 1:                    # 生成树已成形，提前收工
                break

    mst.sort()                                       # 按 (u, v) 字典序输出
    print("\n".join(f"{u} {v}" for u, v in mst))


if __name__ == "__main__":
    solve()
