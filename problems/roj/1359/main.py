#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 07:02
# update_at: 2026-09-30 07:02

import sys
from collections import deque
from collections.abc import Iterator

SIZE = 10  # 题面固定 10×10


def neighbors(cell: tuple[int, int]) -> Iterator[tuple[int, int]]:
    """产出上下左右四个相邻格（可能越界，由调用点判边界）。"""
    r, c = cell
    yield r - 1, c
    yield r + 1, c
    yield r, c - 1
    yield r, c + 1


def solve() -> None:
    # 按行优先读扁平 token：真实数据里有测例只给了 9 行，缺的行自然补 0（仍是 0，不影响答案）。
    grid = [[0] * SIZE for _ in range(SIZE)]
    for i, value in enumerate(map(int, sys.stdin.buffer.read().split())):
        grid[i // SIZE][i % SIZE] = value  # i 超过 100 的部分被丢弃

    outside = [[False] * SIZE for _ in range(SIZE)]
    queue: deque[tuple[int, int]] = deque()

    # 边界上的 0 都是外部：从它们洪水填充，能走到的 0 全部属于图形外。
    for r, c in [
        (r, c)
        for r in range(SIZE)
        for c in range(SIZE)
        if grid[r][c] == 0 and (r in (0, SIZE - 1) or c in (0, SIZE - 1))
    ]:
        if not outside[r][c]:
            outside[r][c] = True
            queue.append((r, c))

    while queue:
        r, c = queue.popleft()
        for nr, nc in neighbors((r, c)):
            in_board = 0 <= nr < SIZE and 0 <= nc < SIZE
            if in_board and grid[nr][nc] == 0 and not outside[nr][nc]:
                outside[nr][nc] = True
                queue.append((nr, nc))

    # 剩下没被外部染色到的 0，就是被 * 围住的内部点，个数即面积。
    print(sum(grid[r][c] == 0 and not outside[r][c] for r in range(SIZE) for c in range(SIZE)))


if __name__ == "__main__":
    solve()
