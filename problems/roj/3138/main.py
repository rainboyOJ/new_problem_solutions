#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 20:05
# update_at: 2026-10-01 20:05

import sys
from operator import add

NEG = -10**9  # 不可达状态；最大答案不超过 2500 * 100，这个负数远小于它


def advance(state: list[list[int]], grid: list[list[int]], m: int, n: int, step: int) -> list[list[int]]:
    """由「走到第 step 条对角线」的状态推出「第 step+1 条对角线」的状态。

    两条路都只向右/下走，于是第 k 步（从 0 数）一定停在第 k+1 条反对角线上：
    行号 r 决定列号 k-r，两条路的状态只需记两个行号 (i, j)。两条路同时出发、
    同时到达，所以它们永远处在同一条对角线上，这正是可以同步转移的理由。
    """
    rows = range(max(0, step - n + 1), min(m - 1, step) + 1)  # 本对角线上的合法行号
    lo, hi = rows.start, rows.stop - 1
    values = [grid[r][step - r] for r in rows]                 # 本对角线每格的好感度
    fresh = [[NEG] * (m + 1) for _ in range(m + 1)]
    for r, value in zip(rows, values):
        i = r + 1
        # 一条路走到本对角线第 r 行，来路只能是上一条对角线的第 r-1 行或第 r 行；
        # 先对这两行逐列取 max 得到「纵向来路」，再和右邻错位取 max 补上「横向来路」。
        # 来路与被更新的格子无关，所以同一份 incoming 能整片写给第 r+1 行。
        from_row = list(map(max, state[i - 1], state[i]))
        incoming = list(map(max, from_row, from_row[1:]))
        gain = [value + other for other in values]  # 两条路分处两格：两格好感度都计入
        gain[r - lo] = value                        # 两条路同处一格：整格只计入一次
        fresh[i][lo + 1:hi + 2] = map(add, incoming[lo:hi + 1], gain)
    return fresh


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    m, n = data[0], data[1]
    grid = [data[2 + r * n: 2 + (r + 1) * n] for r in range(m)]

    # 状态表按行号索引，规模是 m*m；转置不改变答案（下/右互换，并集权重不变），
    # 所以让 m 取较小的一维，表的大小和每条对角线的工作量都收缩到 O(min(m,n))。
    if m > n:
        m, n = n, m
        grid = [list(col) for col in zip(*grid)]

    # 两条路都从 (1,1) 出发、(m,n) 结束。起点必然被两条路同时占用，
    # 按"每人只帮一次"的规则只计一份权重；终点同理，由最终的 state[m][m] 只加一次。
    state = [[NEG] * (m + 1) for _ in range(m + 1)]
    state[1][1] = grid[0][0]
    for step in range(1, m + n - 1):
        state = advance(state, grid, m, n, step)
    print(state[m][m])


if __name__ == "__main__":
    solve()
