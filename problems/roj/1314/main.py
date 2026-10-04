#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 04:41
# update_at: 2026-09-30 04:49

import sys

# 马的控制点：马自身 (0,0) 偏移 + 日字 8 个方向，一个 (dx, dy) 家族
HORSE_OFFSETS = (
    [(0, 0)]
    + [(dx, dy) for dx, dy in ((1, 2), (2, 1), (2, -1), (1, -2))]  # 右侧 4 个日字
    + [(dx, dy) for dx, dy in ((-1, -2), (-2, -1), (-2, 1), (-1, 2))]  # 左侧 4 个日字
)


def count_paths(n: int, m: int, blocked: set[tuple[int, int]]) -> int:
    """统计卒从 (0,0) 只向右/向下走到 (n,m)、避开 blocked 中马控制点的路径数。"""
    # 逐行滚动：row[j] 是到达当前行 (i, j) 的路径数
    row = [1] * (m + 1)
    for j in range(m + 1):  # 第 0 行只能一直向右，遇到控制点后右侧全部不可达
        if (0, j) in blocked:
            row[j:] = [0] * (m + 1 - j)
            break

    for i in range(1, n + 1):
        left = 0 if (i, 0) in blocked else row[0]  # 每行第 0 列只能从上面来
        row[0] = left
        for j in range(1, m + 1):
            # 上方 row[j]（还未被覆盖）+ 左方 left；控制点本身路径数为 0
            left = 0 if (i, j) in blocked else row[j] + left
            row[j] = left

    return row[m]


def solve() -> None:
    n, m, x, y = map(int, sys.stdin.buffer.read().split())
    blocked = {(x + dx, y + dy) for dx, dy in HORSE_OFFSETS}  # 马的 9 个控制点

    print(count_paths(n, m, blocked))


if __name__ == "__main__":
    solve()
