#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 02:01
# update_at: 2026-09-30 02:02

import sys
from collections import deque

N = 5  # 迷宫固定 5×5


def bfs_path(maze: list[list[int]]) -> list[tuple[int, int]]:
    """BFS 求左上到右下的最短路，返回从起点到终点的坐标序列（保证唯一解）。"""
    # prev 记录每个格子从哪个格子走来，同时充当 vis：起点没有前驱，用 None 哨兵
    prev: dict[tuple[int, int], tuple[int, int] | None] = {(0, 0): None}
    queue = deque([(0, 0)])
    while queue:
        r, c = queue.popleft()
        for nr, nc in ((r - 1, c), (r + 1, c), (r, c - 1), (r, c + 1)):  # 上下左右
            inside = 0 <= nr < N and 0 <= nc < N and not maze[nr][nc]
            if inside and (nr, nc) not in prev:
                prev[(nr, nc)] = (r, c)  # 首次到达即最短，登记前驱
                queue.append((nr, nc))

    path: list[tuple[int, int]] = []  # 从终点沿前驱回溯，再反转
    cur: tuple[int, int] | None = (N - 1, N - 1)
    while cur is not None:
        path.append(cur)
        cur = prev[cur]
    return path[::-1]


def solve() -> None:
    tokens = sys.stdin.buffer.read().split()
    maze = [[int(v) for v in tokens[r * N : r * N + N]] for r in range(N)]  # 5 行迷宫

    print('\n'.join(f'({r}, {c})' for r, c in bfs_path(maze)))


if __name__ == "__main__":
    solve()
