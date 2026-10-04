#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 23:54
# update_at: 2026-09-29 23:54

import sys

DIRS = ((-1, 0), (1, 0), (0, -1), (0, 1))  # 上、下、左、右四个相邻方向


def reachable(maze: list[str], ha: int, la: int, hb: int, lb: int) -> bool:
    """能否从 A(ha, la) 走到 B(hb, lb)：只经 '.'、四方向相邻；A、B 任一是 '#' 直接不通。"""
    n = len(maze)
    if maze[ha][la] == '#' or maze[hb][lb] == '#':
        return False
    a, b = (ha, la), (hb, lb)
    seen = {a}
    stack = [a]
    while stack:
        cell = stack.pop()
        if cell == b:
            return True
        r, c = cell
        for dr, dc in DIRS:
            nr, nc = r + dr, c + dc
            # 先判在界内，短路顺序保证不会越界读 maze
            can_go = 0 <= nr < n and 0 <= nc < n and maze[nr][nc] == '.' and (nr, nc) not in seen
            if can_go:
                seen.add((nr, nc))  # 入栈即标记，防止同一点被重复展开成环
                stack.append((nr, nc))
    return False


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    out: list[str] = []
    k = int(next(data))  # 测试数据组数

    for _ in range(k):
        n = int(next(data))  # 迷宫规模 n * n
        maze = [next(data).decode() for _ in range(n)]
        ha, la, hb, lb = (int(next(data)) for _ in range(4))  # A、B 的行列，均从 0 开始
        can_walk = reachable(maze, ha, la, hb, lb)
        out.append('YES' if can_walk else 'NO')

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
