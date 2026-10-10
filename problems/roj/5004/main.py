#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 10:37
# update_at: 2026-10-08 11:02

# 区间加 + 区间求和。记差分 d_i = a_i - a_{i-1}（a_0 = 0），则
#   [x,y] 加 z  <=>  d_x += z、d_{y+1} -= z
#   前缀和 S_x = Σ a_i = Σ d_i·(x-i+1) = (x+1)·Σd_i - Σ i·d_i
# 于是用两棵树状数组分别维护 d_i 与 i·d_i，两种操作都降到 O(log n)。

import sys


def point_add(tree_d: list[int], tree_w: list[int], size: int, idx: int, val: int) -> None:
    """在差分下标 idx 处加 val：两棵树同步向上跳，权值树存 i·d_i。"""
    weighted = val * idx  # 权重是「原始下标」，不是树上的节点编号，别写成 val * i
    i = idx
    while i <= size:
        tree_d[i] += val
        tree_w[i] += weighted
        i += i & -i


def prefix_sum(tree_d: list[int], tree_w: list[int], idx: int) -> int:
    """下标 1..idx 的元素和 S_idx = (idx+1)·Σd_i - Σ i·d_i。"""
    sum_d = sum_w = 0
    i = idx
    while i > 0:
        sum_d += tree_d[i]
        sum_w += tree_w[i]
        i -= i & -i
    return (idx + 1) * sum_d - sum_w


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    tree_d = [0] * (n + 2)
    tree_w = [0] * (n + 2)

    # 边读入原数组边转成差分：d_i = a_i - a_{i-1}，a_0 视为 0
    last = 0
    for i in range(1, n + 1):
        a = next(data)
        point_add(tree_d, tree_w, n, i, a - last)
        last = a

    out: list[str] = []
    for _ in range(m):
        op = next(data)
        x, y = next(data), next(data)
        if op == 1:
            z = next(data)
            point_add(tree_d, tree_w, n, x, z)
            point_add(tree_d, tree_w, n, y + 1, -z)  # y+1 越界时 while 不执行，相当于只改 d_x
        else:
            out.append(str(prefix_sum(tree_d, tree_w, y) - prefix_sum(tree_d, tree_w, x - 1)))

    if out:
        print('\n'.join(out))


if __name__ == "__main__":
    solve()
