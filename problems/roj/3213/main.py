#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 02:11
# update_at: 2026-10-02 02:17

import sys

INF = 10 ** 18  # 远超任何可行总花费：MST 最多约 15*1000，分组总和只会更小


def mst_weight(sub: int, edges: list[tuple[int, int, int]]) -> int:
    """只允许 sub 内的宝石参与时，把它们连成一体的最小花费；连不通返回 INF。

    Kruskal：edges 已按代价升序，两端都落在 sub 内的边才可用。并到"点数 - 1 条边"
    就提前收工，稠密图上不必白扫剩余边。
    """
    vertices = sub.bit_count()
    # 只给 sub 里的点建并查集：range(sub.bit_length()) 恰好覆盖 sub 可能出现的所有位
    parent = {i: i for i in range(sub.bit_length()) if sub >> i & 1}

    def find(x: int) -> int:
        while parent[x] != x:
            parent[x] = parent[parent[x]]                # 路径压缩，顺手改写成迭代
            x = parent[x]
        return x

    merged = weight = 0
    for u, v, t in edges:
        if not (sub >> u & 1 and sub >> v & 1):
            continue                                     # 有端点不在 sub 内，这条边用不上
        ru, rv = find(u), find(v)
        if ru == rv:
            continue
        parent[ru] = rv
        merged += 1
        weight += t
        if merged == vertices - 1:
            return weight                                # n-1 条边到齐，已经是一棵树
    return weight if merged == vertices - 1 else INF     # 没并满 = 这个点集本身不连通


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    a = [next(data) for _ in range(n)]
    edges = sorted([(next(data), next(data), next(data)) for _ in range(m)], key=lambda e: e[2])
    full = (1 << n) - 1

    # total[sub]：sub 里所有宝石的能量之和。去掉最低位再加回它，一次 O(2^n) 打表。
    total = [0] * (1 << n)
    for sub in range(1, 1 << n):
        low = sub & -sub
        total[sub] = total[sub ^ low] + a[low.bit_length() - 1]

    # cost[sub]：只调平 sub 内部所需的最小花费。总能量不为 0 的集合永远调不平，代价记 INF。
    cost = [0] + [mst_weight(sub, edges) if total[sub] == 0 else INF
                  for sub in range(1, 1 << n)]

    # ok[sub]：sub 能否"独立调平"——总能量为 0（进出的能量相等）且内部连通（能量传得动）。
    ok = bytearray(1 << n)
    for sub in range(1, 1 << n):
        ok[sub] = total[sub] == 0 and cost[sub] < INF

    # dp[sub]：把 sub 拆成若干个可独立调平的块的最小总花费。只枚举含 sub 最低位的块，
    # 因为每一份拆法里含最低位的块唯一，这样同一份拆法不会换着顺序被重复枚举。
    dp = [0] + [INF] * full
    for sub in range(1, 1 << n):
        low = sub & -sub
        rest = sub ^ low
        block, best = rest, INF
        while True:
            cand = low | block                               # 候选块：sub 中含最低位的子集
            if ok[cand]:
                best = min(best, dp[sub ^ cand] + cost[cand])
            if block == 0:
                break
            block = (block - 1) & rest                       # 枚举 rest 的所有子集
        dp[sub] = best
    print(dp[full] if dp[full] < INF else "Impossible")


if __name__ == "__main__":
    solve()
