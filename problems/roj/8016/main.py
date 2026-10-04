#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 17:15
# update_at: 2026-10-02 17:15

import sys


def flood_fill(start: tuple[int, int], grid: list[str], seen: set[tuple[int, int]]) -> None:
    """从 start 出发，把上下左右连通的同一片字母区域全部标记为已访问。"""
    stack = [start]
    while stack:
        x, y = stack.pop()
        for adj in ((x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1)):
            nx, ny = adj
            in_map = 0 <= nx < len(grid) and 0 <= ny < len(grid[nx])
            if in_map and grid[nx][ny].isalpha() and adj not in seen:
                seen.add(adj)  # 入栈前先标记，避免同一个格子被重复入栈
                stack.append(adj)


def solve() -> None:
    lines = sys.stdin.read().splitlines()
    n = int(lines[0])
    grid = lines[1:n + 1]  # 每行原样保留前导空格：空格是大海，'*' 是阻隔，字母是人家

    seen: set[tuple[int, int]] = set()
    families = 0
    for r, row in enumerate(grid):
        for c, ch in enumerate(row):
            if ch.isalpha() and (r, c) not in seen:
                families += 1  # 发现一个没访问过的字母点，就多了一个新家族
                flood_fill((r, c), grid, seen)

    print(families)


if __name__ == "__main__":
    solve()
