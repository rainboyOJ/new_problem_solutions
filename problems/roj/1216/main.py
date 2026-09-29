#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 00:01
# update_at: 2026-09-30 00:01

import sys

BLACK = '.'  # 可走的黑色瓷砖
START = '@'  # 黑色瓷砖，且是出发点
DIRS = ((-1, 0), (1, 0), (0, -1), (0, 1))  # 上、下、左、右四个相邻方向
TILES = frozenset('.#@')  # 瓷砖字符；用它把数字流和网格字符流分开


def count_reachable(grid: list[str], h: int, w: int, start: tuple[int, int]) -> int:
    """从 start 出发能到达的黑砖数（含起点）：一次洪水填充，走过的格子染色不再回访。"""
    board = [list(row) for row in grid]  # 就地染色需要可变副本
    board[start[0]][start[1]] = '#'  # 起点即已访问
    stack = [start]
    count = 0
    while stack:
        r, c = stack.pop()
        count += 1
        for dr, dc in DIRS:
            nr, nc = r + dr, c + dc
            # 先判在界内，短路顺序保证越界时不会读数组
            if 0 <= nr < h and 0 <= nc < w and board[nr][nc] == BLACK:
                board[nr][nc] = '#'  # 入栈即标记，同一点不会被重复压栈
                stack.append((nr, nc))
    return count


def solve() -> None:
    text = sys.stdin.buffer.read().decode()
    sizes = iter(int(token) for token in text.split() if token.isdigit())  # 只有 W、H 是数字
    tiles = [ch for ch in text if ch in TILES]  # 网格字符跨行连续，按原始顺序排好
    out: list[str] = []
    pos = 0

    while True:
        w, h = next(sizes), next(sizes)  # x 方向、y 方向瓷砖数
        if w == 0 and h == 0:  # "0 0" 表示输入结束
            break
        # 连续取 h*w 个瓷砖字符，再按每行 w 个切成网格
        grid = [''.join(tiles[pos + r * w:pos + (r + 1) * w]) for r in range(h)]
        pos += h * w
        # 起点字符 '@' 在每个数据集合中唯一出现一次
        start = next((r, c) for r in range(h) for c in range(w) if grid[r][c] == START)
        out.append(str(count_reachable(grid, h, w, start)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
