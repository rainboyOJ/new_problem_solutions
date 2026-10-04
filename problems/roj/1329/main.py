#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-02-14 10:30
# update_at: 2026-10-04 15:03

import sys
from collections import deque


def flood_fill(grid: list[list[str]], sr: int, sc: int) -> None:
    """从 (sr, sc) 出发把整个四连通细胞抹成 '0'（原地标记，避免 visited 数组）。"""
    grid[sr][sc] = '0'
    queue = deque([(sr, sc)])
    while queue:
        r, c = queue.popleft()
        for nr, nc in ((r - 1, c), (r + 1, c), (r, c - 1), (r, c + 1)):
            inside = 0 <= nr < len(grid) and 0 <= nc < len(grid[0])
            if inside and grid[nr][nc] != '0':
                grid[nr][nc] = '0'  # 入队即标记，保证每格至多入队一次
                queue.append((nr, nc))


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n, m = int(next(data)), int(next(data))  # 两个位置量先命名
    grid = [list(next(data).decode()) for _ in range(n)]  # 每行是完整 token，行内无空格

    cells = 0
    for r in range(n):
        for c in range(m):
            is_cell = grid[r][c] != '0'  # 尚未抹掉的细胞数字 = 一个新细胞的种子
            if is_cell:
                cells += 1
                flood_fill(grid, r, c)

    print(cells)


if __name__ == "__main__":
    solve()
