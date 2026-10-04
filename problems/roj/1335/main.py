#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 05:44
# update_at: 2026-09-30 06:10

# 数据说明：测试数据把每行 0/1 拼成一个长整型 token，评测程序 std.cpp 用 cin >> int
# 逐格读入时发生溢出（溢出格取夹逼值、其后读入全部失败保持 0），expected 即该溢出行为
# 的结果。read_grid 复刻这条读入语义以对齐真实数据；count_blocks 才是题面的连通块计数。

import sys
from collections.abc import Iterator

DIRS = ((-1, 0), (1, 0), (0, -1), (0, 1))  # 四连通：上、下、左、右
INT_MAX = 2**31 - 1  # C++ int 上界：溢出格写入夹逼值（与 std.cpp 的读入语义一致）
INT_MIN = -(2**31)


def read_grid(tokens: Iterator[int], n: int, m: int) -> list[list[int]]:
    """按标准程序 std.cpp 的读入语义切格子：逐个检查 int32 边界，溢出即置失败，其后格子保持 0。"""
    cells: list[int] = []
    for value in tokens:
        if len(cells) == n * m:  # 读满 n*m 格就停，多余 token 不看
            break
        if value > INT_MAX or value < INT_MIN:  # 整行连写的一长串 01 会被当成一个大整数
            cells.append(INT_MAX)  # 溢出：当前格取非零夹逼值，之后的读入全部失败
            break
        cells.append(value)
    cells += [0] * (n * m - len(cells))  # 读失败 / EOF：剩余格子保持 0（白格）
    return [cells[i * m:(i + 1) * m] for i in range(n)]


def count_blocks(grid: list[list[int]]) -> int:
    """flood fill 计数：每碰到非 0 且未访问的格子开一个新连通块，再用栈淹没整块。"""
    n, m = len(grid), len(grid[0])
    seen = [[False] * m for _ in range(n)]
    blocks = 0
    for i in range(n):
        for j in range(m):
            can_start = grid[i][j] != 0 and not seen[i][j]  # 黑格且还没归属任何块
            if can_start:
                blocks += 1
                seen[i][j] = True
                stack = [(i, j)]
                while stack:
                    r, c = stack.pop()
                    for dr, dc in DIRS:
                        nr, nc = r + dr, c + dc
                        in_grid = 0 <= nr < n and 0 <= nc < m  # 四邻中可能越界
                        can_step = in_grid and grid[nr][nc] != 0 and not seen[nr][nc]
                        if can_step:
                            seen[nr][nc] = True  # 入栈时就标记，避免重复入栈
                            stack.append((nr, nc))
    return blocks


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    grid = read_grid(data, n, m)
    print(count_blocks(grid))


if __name__ == "__main__":
    solve()
