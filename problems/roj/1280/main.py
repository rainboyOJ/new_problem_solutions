#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys

DIRS = ((-1, 0), (1, 0), (0, -1), (0, 1))  # 上下左右四个相邻方向


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    R, C = next(data), next(data)
    grid = [[next(data) for _ in range(C)] for _ in range(R)]

    # 按高度从小到大处理：算 (r,c) 时，比它低的邻格必然已算完，
    # 等价于记忆化 dfs，但不需要递归（最长滑坡可达 R*C 级深度）。
    length: dict[tuple[int, int], int] = {}  # (r,c) -> 从该格出发的最长滑坡
    for h, r, c in sorted((grid[r][c], r, c) for r in range(R) for c in range(C)):
        lower = (  # 所有比当前格低、且在边界内的相邻格
            length[(r + dr, c + dc)]
            for dr, dc in DIRS
            if 0 <= r + dr < R and 0 <= c + dc < C and grid[r + dr][c + dc] < h
        )
        length[(r, c)] = 1 + max(lower, default=0)  # 一步都不滑也算了自身

    print(max(length.values()))


if __name__ == "__main__":
    solve()
