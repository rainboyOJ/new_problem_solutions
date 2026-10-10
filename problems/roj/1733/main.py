#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 19:20
# update_at: 2026-10-07 19:20

import sys
from heapq import heappop, heappush

# 线段树节点：(本段差分数组之和, 本段内「自段左端起算的最大前缀和」, 取到它的最大下标)。
# 差分数组 d 的前缀和 d[0]+...+d[l] 就是 mx[l]（1-based 的 mx[l+1]）。
type Node = tuple[int, int, int]

type Query = tuple[int, int]  # (询问左端点 x, 询问编号 id)，1-based
type Tree = list[Node]        # 迭代式线段树，tree[i] 就是节点 i（叶子在 [size, 2*size)）
type Buckets = list[list[Query]]  # by_y[y]：右端点为 y 的全部询问

NEG = -10**9  # 哨兵：补齐用的空叶子，其「最大前缀和」永不可能是答案


def merge(left: Node, right: Node) -> Node:
    """合并相邻两段，得到「最大前缀和 + 最大下标」；平手取更靠右的下标。"""
    total = left[0] + right[0]
    cross = left[0] + right[1]   # 跨过分界的候选：左段整段和 + 右段的最大前缀和
    if cross >= left[1]:         # 平手取 right[2]（更靠右的下标）
        return (total, cross, right[2])
    return (total, left[1], left[2])


def point_add(tree: Tree, size: int, pos: int, delta: int) -> None:
    """给差分数组的第 pos 位（0-based）加上 delta，并沿路重算祖先。"""
    i = size + pos
    total, best, arg = tree[i]
    tree[i] = (total + delta, best + delta, arg)
    i >>= 1
    while i:
        tree[i] = merge(tree[2 * i], tree[2 * i + 1])
        i >>= 1


def add_prefix(tree: Tree, size: int, n: int, p: int) -> None:
    """把 mx[1..p] 整体加一：差分数组上只有第 0 位 +1、第 p 位 -1（p 是 0-based 的 p）。"""
    point_add(tree, size, 0, 1)
    if p < n:
        point_add(tree, size, p, -1)


def prefix_max(tree: Tree, size: int, count: int) -> Node:
    """求 mx[1..count] 的最大值（存在 best 位）及取到它的最大左端点（0-based 存在 arg 位）。"""
    node, lo, hi = 1, 0, size
    acc: Node | None = None
    while True:
        if count == hi - lo:                       # 整段都被覆盖，直接取这一段
            return tree[node] if acc is None else merge(acc, tree[node])
        mid = (lo + hi) >> 1
        if count <= mid - lo:                      # 只在左孩子里找
            node, hi = 2 * node, mid
        else:                                      # 左孩子整段收下，再进右孩子找剩余部分
            acc = tree[2 * node] if acc is None else merge(acc, tree[2 * node])
            count -= mid - lo
            node, lo = 2 * node + 1, mid


def answer_all(n: int, a: list[int], pos_of_val: list[int],
               by_y: Buckets, m: int) -> tuple[list[int], list[int]]:
    """扫右端点 i，用线段树维护 mx[l] = l + cnt(l, i)，在每个询问的闭包右端点处结算答案。"""
    size = 1
    while size < n:
        size <<= 1
    # 叶子 i 表示差分数组 d[i]（0-based），它的前缀和就是 mx[i+1]。初值 d[i] = 1。
    # 下标 [n, size) 是补齐出来的空叶子：和不贡献（sum = 0）、最大前缀和取哨兵。
    tree: Tree = [(0, NEG, i) for i in range(2 * size)]
    for i in range(n):
        tree[size + i] = (1, 1, i)
    for i in range(size - 1, 0, -1):
        tree[i] = merge(tree[2 * i], tree[2 * i + 1])

    ans_l = [0] * m
    ans_r = [0] * m
    heap: list[tuple[int, int]] = []  # 存 (-x, id)，堆顶就是 x 最大的未结算询问
    answered = 0                      # 已结算的询问数，全部结算完就不必再往后扫
    for right in range(1, n + 1):
        w = a[right]
        # 值对 (w-1, w) 与 (w, w+1)：另一端已在 [1, right] 内出现时，从 right 起
        # 它对每个 l <= 那个下标 的区间 [l, right] 都成立，于是前缀 [1, 那个下标] 加一。
        for v in (w - 1, w + 1):
            other = pos_of_val[v]                  # 未出现的值记 0，条件自然不成立
            if 0 < other <= right:
                add_prefix(tree, size, n, other)
        for query in by_y[right]:
            heappush(heap, (-query[0], query[1]))
        while heap:
            neg_x, id = heap[0]
            _total, mx_best, mx_arg = prefix_max(tree, size, -neg_x)
            if mx_best != right:                   # 堆顶（x 最大）都做不到，其余更做不到
                break
            heappop(heap)
            ans_l[id], ans_r[id] = mx_arg + 1, right
            answered += 1
        if answered == m:                  # 所有询问都有答案了，后面的右端点只可能更长
            break
    return ans_l, ans_r


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    a = [0] * (n + 1)
    pos_of_val = [0] * (n + 2)                     # 值 v 所在下标，0 表示还没出现
    for i in range(1, n + 1):
        a[i] = next(data)
        pos_of_val[a[i]] = i

    m = next(data)
    by_y: Buckets = [[] for _ in range(n + 1)]
    for id in range(m):
        x, y = next(data), next(data)
        by_y[y].append((x, id))

    ans_l, ans_r = answer_all(n, a, pos_of_val, by_y, m)
    out = [f"{ans_l[i]} {ans_r[i]}" for i in range(m)]
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
