#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 10:20
# update_at: 2026-10-02 10:20

import sys
from functools import cache
from itertools import chain
from math import sqrt

SIZE = 8      # 棋盘边长固定为 8
INF = 10**18  # 矩形小到一刀也下不去时的不可行代价

PREFIX: list[list[int]] = []  # (SIZE+1) x (SIZE+1) 的二维前缀和，由 solve 填入


def prefix_of(cells: list[int]) -> list[list[int]]:
    """把行优先读入的 64 个格子分值变成二维前缀和，使任意子矩形和 O(1) 可求。"""
    P = [[0] * (SIZE + 1) for _ in range(SIZE + 1)]
    for r in range(SIZE):
        for c in range(SIZE):
            P[r + 1][c + 1] = P[r][c + 1] + P[r + 1][c] - P[r][c] + cells[SIZE * r + c]
    return P


def box(r1: int, c1: int, r2: int, c2: int) -> int:
    """闭区间矩形 [r1,r2] x [c1,c2] 的分值之和。"""
    return PREFIX[r2 + 1][c2 + 1] - PREFIX[r1][c2 + 1] - PREFIX[r2 + 1][c1] + PREFIX[r1][c1]


def cuts(r1: int, c1: int, r2: int, c2: int):
    """枚举“割下一块矩形、剩下部分仍是矩形”的所有一刀，产出 (割下的块, 剩下的块)。"""
    return chain(
        (((r1, c1, i, c2), (i + 1, c1, r2, c2)) for i in range(r1, r2)),  # 割走上半
        (((i + 1, c1, r2, c2), (r1, c1, i, c2)) for i in range(r1, r2)),  # 割走下半
        (((r1, c1, r2, j), (r1, j + 1, r2, c2)) for j in range(c1, c2)),  # 割走左半
        (((r1, j + 1, r2, c2), (r1, c1, r2, j)) for j in range(c1, c2)),  # 割走右半
    )


@cache
def best(r1: int, c1: int, r2: int, c2: int, k: int) -> int:
    """把矩形切成 k 块时各块分值平方和的最小值（均方差只与它相差一个常数）。"""
    if k == 1:
        return box(r1, c1, r2, c2) ** 2
    return min(
        # 割下的那块就此定稿，剩下那块还要再切 k-1 刀
        (box(*peeled) ** 2 + best(*kept, k - 1) for peeled, kept in cuts(r1, c1, r2, c2)),
        default=INF,  # 单格矩形切不出两块
    )


def solve() -> None:
    global PREFIX
    data = list(map(int, sys.stdin.buffer.read().split()))
    n, *cells = data
    PREFIX = prefix_of(cells)
    total = PREFIX[SIZE][SIZE]
    s2 = best(0, 0, SIZE - 1, SIZE - 1, n)  # Σx² 的最小值
    # 均方差 = sqrt(Σx²/n - (Σx/n)²)：n 与总分 Σx 固定，所以只需最小化 Σx²
    print(f"{sqrt(s2 / n - (total / n) ** 2):.3f}")


if __name__ == "__main__":
    solve()
