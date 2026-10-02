#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 08:02
# update_at: 2026-10-02 08:02

import sys

NEG = -10**9  # 不可达状态的哨兵（好感度非负，可达值恒 >= 0）


def advance(prev: list[list[int]], grid: list[list[int]], k: int, m: int, n: int) -> list[list[int]]:
    """推进一层：求两条路的行号和都恰好为 k 时，能拿到的最大好感度和。

    行号和为 k 的格子 (x, k-x) 只能由上一层的 (x-1, k-x) 向下走到达，
    或由 (x, k-x-1) 向右走到达，所以两条路各自只需尝试两种来向，共 4 种组合。
    """
    cur = [[NEG] * (m + 1) for _ in range(m + 1)]
    lo, hi = max(1, k - n), min(m, k - 1)  # 第 k 层合法行号：列号 k-x 必须落在 1..n
    for x1 in range(lo, hi + 1):
        v1 = grid[x1 - 1][k - x1 - 1]  # 路 1 所在格子的好感度
        for x2 in range(lo, hi + 1):
            best = max(
                prev[p1][p2]
                for p1 in (x1, x1 - 1)  # 来向：上一层同行（向右走来）/ 上一层上一行（向下走来）
                for p2 in (x2, x2 - 1)
            )
            if best == NEG:  # 两条路都到不了的格子对，整格跳过
                continue
            # x1 == x2 时两路重合格子（同层列号也相同），每人只帮一次，好感度只加一次
            cur[x1][x2] = best + v1 + (grid[x2 - 1][k - x2 - 1] if x1 != x2 else 0)
    return cur


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    m, n = next(data), next(data)
    grid = [[next(data) for _ in range(n)] for _ in range(m)]

    # 按行号和 k 分层的二维 DP：f[x1][x2] 表示两条路分别走到 (x1, k-x1)、(x2, k-x2)
    # 时的最大好感度和。起点 k=2：两路都在 (1,1)，端点好感度为 0。
    layer = [[NEG] * (m + 1) for _ in range(m + 1)]
    layer[1][1] = grid[0][0]
    for k in range(3, m + n + 1):
        layer = advance(layer, grid, k, m, n)
    print(layer[m][m])


if __name__ == "__main__":
    solve()
