#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 02:01
# update_at: 2026-09-30 02:04

import sys

WALL = ord('#')  # 网格按字节读入，'#' 的字节值 35 就是"不可通行"的判据

# 四个方向的 (行增量, 列增量)：上、下、左、右
DIRS: tuple[tuple[int, int], ...] = ((-1, 0), (1, 0), (0, -1), (0, 1))


def find(grid: list[bytes], key: int) -> tuple[int, int]:
    """定位标记字符 key（'S' 或 'T'）所在的 (行, 列)；题面保证它出现且只出现一次。"""
    return next(
        (r, c)
        for r, row in enumerate(grid)
        for c, ch in enumerate(row)
        if ch == key
    )


def shortest_steps(
    grid: list[bytes], n: int, m: int, start: tuple[int, int], goal: tuple[int, int]
) -> int | None:
    """四方向 BFS 返回 start→goal 的最少步数（不含起点）；不可达返回 None。

    边权全为 1，所以按层扩展：frontier 是恰好 steps 步能站到的全部格子，
    命中 goal 的那层号就是答案。格子用一维编号 r*m+c 标记，入队即标记。
    """
    seen = bytearray(n * m)
    seen[start[0] * m + start[1]] = 1
    frontier = [start]
    steps = 0
    while frontier:
        nxt: list[tuple[int, int]] = []  # 再多走一步能站到的格子
        for r, c in frontier:
            if (r, c) == goal:
                return steps
            for dr, dc in DIRS:
                nr, nc = r + dr, c + dc
                in_board = 0 <= nr < n and 0 <= nc < m  # 先判界，避免负下标悄悄读到别的行
                can_step = in_board and grid[nr][nc] != WALL and not seen[nr * m + nc]
                if can_step:
                    seen[nr * m + nc] = 1  # 入队即标记，同一个格子只展开一次
                    nxt.append((nr, nc))
        frontier, steps = nxt, steps + 1
    return None


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n = int(next(data))
    m = int(next(data))
    grid: list[bytes] = [next(data) for _ in range(n)]  # 每行是一个整体 token，不按字符拆分

    steps = shortest_steps(grid, n, m, find(grid, ord('S')), find(grid, ord('T')))
    if steps is not None:  # 不连通时官方数据为空输出，这里同样不打印任何内容
        print(steps)


if __name__ == "__main__":
    solve()
