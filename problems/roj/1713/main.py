#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 17:50
# update_at: 2026-10-07 17:50

import sys
from math import lcm

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Buckets = dict[int, list[tuple[int, int]]]  # 边权 -> 该权值的边表 [(u, v)]


def find(parent: list[int], x: int) -> int:
    """并查集找根：路径减半，顺路把 x 直挂祖父。"""
    while parent[x] != x:
        parent[x] = parent[parent[x]]
        x = parent[x]
    return x


def spans(n: int, buckets: Buckets, d: int, maxw: int) -> bool:
    """只保留边权为 d 的倍数的边（记作 G_d）后，整张图是否连通。"""
    parent = list(range(n + 1))
    comp = n  # 当前连通块个数
    for k in range(d, maxw + 1, d):
        edges = buckets.get(k)
        if edges is None:
            continue
        for u, v in edges:
            ru, rv = find(parent, u), find(parent, v)
            if ru != rv:
                parent[rv] = ru
                comp -= 1
        if comp == 1:  # 已经连通，后面那些桶不必再看
            return True
    return comp == 1


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    buckets: Buckets = {}
    for _ in range(m):
        u, v, w = next(data), next(data), next(data)
        buckets.setdefault(w, []).append((u, v))

    # n = 1（必然 m = 0）只有唯一的空生成树，约定答案为 1
    if n <= 1 or not buckets:
        print(1)
        return

    maxw = max(buckets)  # d 只需枚举到最大边权，更大的 d 一条可用边都没有
    weight_count = {w: len(edges) for w, edges in buckets.items()}  # 每个权值有几条边
    # avail[d] = 边权能被 d 整除的边数（下标 0 占位不用）；不足 n-1 条时 G_d 必然不连通，
    # 这种 d 连并查集都不用建，先用 O(w log w) 的调和级数前缀把它筛掉
    avail = [0] + [sum(weight_count.get(k, 0) for k in range(d, maxw + 1, d))
                   for d in range(1, maxw + 1)]

    ans = 1
    for d in range(1, maxw + 1):
        enough_edges = avail[d] >= n - 1
        if enough_edges and spans(n, buckets, d, maxw):
            ans = lcm(ans, d)  # G_d 连通 ⇔ d 整除某棵生成树的边权 gcd
    print(ans)


if __name__ == "__main__":
    solve()
