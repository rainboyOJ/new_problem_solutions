#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 20:41
# update_at: 2026-09-30 20:41

import sys
from itertools import product

MOD = 10**6  # 题面要求的模数


def valid_rows(m: int) -> list[tuple[int, ...]]:
    """列出一行的所有合法涂法：M 列取 1/2/3，且相邻列颜色不同。"""
    return [
        row
        for row in product(range(1, 4), repeat=m)
        if all(row[c] != row[c + 1] for c in range(m - 1))
    ]


def build_compat(rows: list[tuple[int, ...]], m: int) -> list[list[int]]:
    """上下兼容表：compat[i] 里是与 rows[i] 上下相邻（每列颜色都不同）的行状态编号。"""
    return [
        [j for j, nxt in enumerate(rows) if all(row[c] != nxt[c] for c in range(m))]
        for row in rows
    ]


def propagate(vec: list[int], compat: list[list[int]], steps: int) -> list[int]:
    """行状态计数向量向下推 steps 行：每个状态累加所有能接在它上面的状态。"""
    for _ in range(steps):
        vec = [sum(map(vec.__getitem__, js)) % MOD for js in compat]
    return vec


def count_plans(n: int, m: int, k: int, fixed: tuple[int, ...]) -> int:
    """第 K 行固定时的合法涂法数：固定行上、下两侧分别做行状态 DP 再相乘。"""
    rows = valid_rows(m)
    if fixed not in rows:  # 固定行自己相邻同色，任何延伸都不合法
        return 0
    compat = build_compat(rows, m)
    me = rows.index(fixed)
    touch = compat[me]  # 兼容表对称：能紧贴固定行上/下的行状态

    # 上半段：第 1 行任取合法状态，推到第 K-1 行，再要求它贴住固定行；K=1 时上方为空
    up = 1
    if k > 1:
        vec = propagate([1] * len(rows), compat, k - 2)  # K-1 行共 K-2 次转移
        up = sum(vec[p] for p in touch) % MOD

    # 下半段：从固定行出发推到第 N 行，末行无约束，全部状态求和
    down = 1
    if k < n:
        vec = [1 if i == me else 0 for i in range(len(rows))]
        down = sum(propagate(vec, compat, n - k)) % MOD

    return up * down % MOD


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    n, m, k = data[0], data[1], data[2]
    fixed = tuple(data[3 : 3 + m])
    print(count_plans(n, m, k, fixed))


if __name__ == "__main__":
    solve()
