#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 01:45
# update_at: 2026-09-30 01:45

import sys
from collections import deque

WALKABLE = '.@*'  # 三种可走格子：空地、起点、终点


def bfs(grid: list[str], start: tuple[int, int], goal: tuple[int, int]) -> int:
    """从 start 四连通走到 goal 的最少步数（不含起点，含终点），不可达返回 -1。"""
    m, n = len(grid), len(grid[0])
    dist = {start: 0}                       # 官方计数不含起点：起点距离为 0 步
    q = deque([start])
    while q:
        x, y = q.popleft()
        if (x, y) == goal:
            return dist[(x, y)]
        for nx, ny in ((x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1)):
            in_board = 0 <= nx < m and 0 <= ny < n
            if in_board and (nx, ny) not in dist and grid[nx][ny] in WALKABLE:
                dist[(nx, ny)] = dist[(x, y)] + 1
                q.append((nx, ny))
    return -1


def solve() -> None:
    data = iter(sys.stdin.read().splitlines())   # 迷宫行必须按整行消费，保留行边界
    out: list[str] = []
    while True:
        line = next(data)                         # 每组的头一行
        m, n = map(int, line.split())             # 网格规模，0 0 表示输入结束
        if m == 0 and n == 0:
            break
        grid = [next(data) for _ in range(m)]     # 迷宫的 m 行

        # 单次扫格子，同时记下起点 @ 与终点 *
        start = goal = (-1, -1)
        for i in range(m):
            for j in range(n):
                start = (i, j) if grid[i][j] == '@' else start
                goal = (i, j) if grid[i][j] == '*' else goal

        out.append(str(bfs(grid, start, goal)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
