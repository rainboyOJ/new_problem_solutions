#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 11:08
# update_at: 2026-10-02 11:08

import sys

# 八个邻接方向（不含自身）：三行三屏去掉 dr=0 且 dc=0 的中心格
NEIGHBOR = [(dr, dc) for dr in (-1, 0, 1) for dc in (-1, 0, 1) if dr or dc]  # 8 个方向


def neighbor_mine_count(grid: list[str], r: int, c: int) -> int:
    """格子 (r, c) 八邻域内的地雷数：只统计仍落在雷区里的格子。"""
    n, m = len(grid), len(grid[0])
    return sum(
        grid[r + dr][c + dc] == '*'  # bool 参与求和即 0/1
        for dr, dc in NEIGHBOR
        if 0 <= r + dr < n and 0 <= c + dc < m  # 越界方向直接丢弃，防止负下标回绕
    )


def render(grid: list[str]) -> list[str]:
    """生成输出雷区：地雷格保持 '*'，非地雷格换成八邻域地雷数。"""
    return [
        ''.join(cell if cell == '*' else str(neighbor_mine_count(grid, r, c))
                for c, cell in enumerate(row))
        for r, row in enumerate(grid)
    ]


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    n, m = int(data[0]), int(data[1])
    grid = [line.decode() for line in data[2:2 + n]]  # 每行 m 个字符，相邻无分隔符
    print('\n'.join(render(grid)))


if __name__ == "__main__":
    solve()
