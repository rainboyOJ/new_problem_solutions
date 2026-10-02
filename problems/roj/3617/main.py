#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 10:44
# update_at: 2026-10-02 10:44

import sys
from itertools import combinations
from math import comb

INF = 10**18  # 分值远小于它，只用来标记"还没选够列"的无效状态


def best_score(mat: list[list[int]], take: int, pick: int) -> int:
    """枚举第一维的 take 个下标组合，在第二维上选出 pick 个下标，返回最小分值。

    固定第一维组合后，分值恰好拆成两部分：第二维每个位置上的纵向相邻差之和 v，
    以及第二维任意两位置之间横跨所选行的横向差之和 h；第二维上做一次
    "选 pick 个、末位是 j" 的顺序 DP 即可把两部分拼成完整分值。
    """
    width = len(mat[0])
    # 每行压平成 width×width 的 |差| 方阵：加入某行时用 zip 一次性加到 h 上
    flat = [[abs(x - y) for x in row for y in row] for row in mat]  # len(mat) 个方阵

    best = INF
    for combo in combinations(range(len(mat)), take):
        # 纵向：该位置上相邻所选行之间的差之和（子矩阵内这些边必然存在）
        v = [
            sum(abs(mat[p][b] - mat[q][b]) for p, q in zip(combo, combo[1:]))
            for b in range(width)
        ]
        # 横向：第二维 i、j 相邻时，横跨所有所选行的差之和
        h = [0] * (width * width)
        for p in combo:
            h = [x + y for x, y in zip(h, flat[p])]

        dp = v[:]  # 只选 1 个位置：只有纵向代价
        for _ in range(1, pick):
            cur = [INF] * width
            for j in range(1, width):  # 末位是 j，前一位只能取更小的 i
                base = j * width
                cur[j] = v[j] + min(dp[i] + h[base + i] for i in range(j))
            dp = cur
        best = min(best, min(dp))
    return best


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    n, m, r, c = data[:4]
    cells = data[4:]
    rows = [cells[i * m:(i + 1) * m] for i in range(n)]

    # 枚举组合数更少的一维，另一维留给 DP，两侧取 min(C(n,r), C(m,c))
    if comb(n, r) <= comb(m, c):
        mat, take, pick = rows, r, c
    else:
        mat, take, pick = list(map(list, zip(*rows))), c, r

    print(best_score(mat, take, pick))


if __name__ == "__main__":
    solve()
