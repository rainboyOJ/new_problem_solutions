#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 01:47
# update_at: 2026-09-30 01:54

import sys
from collections import deque

DIRS = ((-1, 0), (1, 0), (0, -1), (0, 1))  # 上、下、左、右四个移动方向


def shortest_path(maze: list[str], rows: int, cols: int) -> int | None:
    """从左上角到右下角最少经过的空地格子数（含起点和终点）；无解返回 None。"""
    # 入队即标记：每个格子只入队一次，出队时它携带的格子数就是最早到达值
    visited = [[False] * cols for _ in range(rows)]
    visited[0][0] = True
    queue = deque([(0, 0, 1)])  # (行, 列, 已经过格子数)，起点本身算 1 格
    while queue:
        row, col, cells = queue.popleft()
        if row == rows - 1 and col == cols - 1:
            return cells  # BFS 按格子数分层，首次出队即最短
        for dr, dc in DIRS:
            nr, nc = row + dr, col + dc
            can_step = 0 <= nr < rows and 0 <= nc < cols and maze[nr][nc] == "."
            if can_step and not visited[nr][nc]:
                visited[nr][nc] = True
                queue.append((nr, nc, cells + 1))
    return None  # 题面保证能走到，无解时不产生任何输出（与参考实现一致）


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    rows, cols = int(data[0]), int(data[1])
    maze = [line.decode() for line in data[2:2 + rows]]  # 每行是一个整体 token
    cells = shortest_path(maze, rows, cols)
    if cells is not None:
        print(cells)


if __name__ == "__main__":
    solve()
