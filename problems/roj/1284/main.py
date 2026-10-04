#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 03:16
# update_at: 2026-09-30 03:16

import sys
from collections.abc import Iterator


def pick_max(grid: list[list[int]]) -> int:
    """从西北角走到东南角、只向东南走，最多能摘到的花生数。

    逐行原地滚动：更新到 (r, c) 时，row_dp[c] 还是上一行（来自上方）的答案，
    row_dp[c-1] 已是本行（来自左方）的答案，取较大者加上当前格的花生即可。
    """
    width = len(grid[0])
    row_dp = [0] * width  # 第 -1 行（虚拟）：网格外收获为 0
    for row in grid:
        for c in range(width):
            from_left = row_dp[c - 1] if c else 0
            row_dp[c] = row[c] + max(row_dp[c], from_left)
    return row_dp[-1]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)

    for _ in range(T):
        R, C = next(data), next(data)
        grid = [[next(data) for _ in range(C)] for _ in range(R)]
        out.append(str(pick_max(grid)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
