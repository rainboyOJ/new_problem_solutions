#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 17:38
# update_at: 2026-09-30 17:38

import sys
from math import isqrt

# 线段树每个节点存 [区间和, 区间最大值, 区间最小值]，下标 1 起
SUM, MX, MN = 0, 1, 2


def build(node: int, lo: int, hi: int, arr: list[int], t: list[list[int]]) -> None:
    """建树：叶子存单个国家的喜欢度，父节点由孩子合并。"""
    if lo == hi:
        v = arr[lo - 1]
        t[node][SUM] = t[node][MX] = t[node][MN] = v
        return
    mid = (lo + hi) // 2
    build(node << 1, lo, mid, arr, t)
    build(node << 1 | 1, mid + 1, hi, arr, t)
    pull(node, t)


def pull(node: int, t: list[list[int]]) -> None:
    """用两个孩子刷新父节点的 [和, 最大, 最小]。"""
    a, b = t[node << 1], t[node << 1 | 1]
    p = t[node]
    p[SUM] = a[SUM] + b[SUM]
    p[MX] = a[MX] if a[MX] > b[MX] else b[MX]
    p[MN] = a[MN] if a[MN] < b[MN] else b[MN]


def push_equal(node: int, lo: int, hi: int, t: list[list[int]]) -> None:
    """把父亲"整段同值"的标记下推给两个孩子，恢复孩子与父亲的一致。

    整段开方可能只改了内部节点，孩子还是开方前的旧值；下次要下探时必须先补齐。
    """
    v = t[node][MX]
    mid = (lo + hi) // 2
    left, right = t[node << 1], t[node << 1 | 1]
    left[SUM], left[MX], left[MN] = v * (mid - lo + 1), v, v
    right[SUM], right[MX], right[MN] = v * (hi - mid), v, v


def apply_sqrt(node: int, lo: int, hi: int, ql: int, qr: int, t: list[list[int]]) -> None:
    """区间开方取整：无交、或整段已是 0/1 时返回；全相等的整段一次改完。"""
    p = t[node]
    if hi < ql or lo > qr or p[MX] <= 1:  # 0 和 1 开方后不变，整棵子树跳过
        return
    if p[MX] == p[MN]:  # 整段同值：全盖住就地开方，否则先下推再下探
        if ql <= lo and hi <= qr:
            v = isqrt(p[MX])
            p[SUM], p[MX], p[MN] = v * (hi - lo + 1), v, v
            return
        push_equal(node, lo, hi, t)
    mid = (lo + hi) // 2
    if ql <= mid:  # 只下探真正有交的孩子，省掉一次空递归
        apply_sqrt(node << 1, lo, mid, ql, qr, t)
    if qr > mid:
        apply_sqrt(node << 1 | 1, mid + 1, hi, ql, qr, t)
    pull(node, t)


def query(node: int, lo: int, hi: int, ql: int, qr: int, t: list[list[int]]) -> int:
    """区间求和：完全落入取区间和；同值段按重叠长度直接算，否则递归两侧。"""
    p = t[node]
    if ql <= lo and hi <= qr:
        return p[SUM]
    if p[MX] == p[MN]:  # 部分重叠的同值段：孩子可能没同步，不必下探
        return p[MX] * (min(hi, qr) - max(lo, ql) + 1)
    mid = (lo + hi) // 2
    total = 0
    if ql <= mid:
        total = query(node << 1, lo, mid, ql, qr, t)
    if qr > mid:
        total += query(node << 1 | 1, mid + 1, hi, ql, qr, t)
    return total


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    arr = [next(data) for _ in range(n)]  # 各国初始喜欢度
    t = [[0, 0, 0] for _ in range(n << 2)]
    build(1, 1, n, arr, t)

    out: list[str] = []
    m = next(data)
    for _ in range(m):
        x, l, r = next(data), next(data), next(data)
        if x == 1:  # 询问 l..r 的开心值总和
            out.append(str(query(1, 1, n, l, r, t)))
        else:  # l..r 每个国家的喜欢度开方取整
            apply_sqrt(1, 1, n, l, r, t)

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
