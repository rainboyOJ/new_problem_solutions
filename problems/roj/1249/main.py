#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 01:46
# update_at: 2026-09-30 01:46

import sys

WATER = 'W'   # 有水
DRY = '.'     # 干燥；同时用它把已访问的水格抹掉，省掉额外的 visited 表
OFFSETS = tuple(
    (dr, dc)
    for dr in (-1, 0, 1)
    for dc in (-1, 0, 1)
    if (dr, dc) != (0, 0)
)  # 八连通：上、下、左、右 + 四条对角线，共 8 个方向


def flood(grid: list[bytearray], row: int, col: int) -> None:
    """从 (row, col) 出发做八连通洪泛，把整片水洼改成 DRY（原地标记已访问）。"""
    grid[row][col] = ord(DRY)
    stack = [(row, col)]
    while stack:
        r, c = stack.pop()
        for dr, dc in OFFSETS:
            nr, nc = r + dr, c + dc
            # 越界判定合并成一次链式比较，比 0 <= nr < n and 0 <= nc < m 少一趟比较
            if -1 < nr < len(grid) and -1 < nc < len(grid[0]) and grid[nr][nc] == ord(WATER):
                grid[nr][nc] = ord(DRY)
                stack.append((nr, nc))


def solve() -> None:
    """统计八连通 'W' 的连通块个数（水洼数）。"""
    data = sys.stdin.buffer.read().split()
    rows = int(data[0])
    grid = [bytearray(line) for line in data[2:2 + rows]]  # 第 2 个 token 起的 rows 行是地图

    ponds = 0
    for r in range(rows):
        for c in range(len(grid[r])):
            if grid[r][c] == ord(WATER):
                ponds += 1          # 每遇到一个尚未被洪泛吞掉的水格，就开出一片新水洼
                flood(grid, r, c)

    print(ponds)


if __name__ == "__main__":
    solve()
