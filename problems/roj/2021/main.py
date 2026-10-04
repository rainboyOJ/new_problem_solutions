#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 03:20
# update_at: 2026-10-01 03:26

import sys
from collections.abc import Iterator

WEST, NORTH, EAST, SOUTH = 1, 2, 4, 8  # 题面的墙编码：1 西 2 北 4 东 8 南
AROUND = ((-1, 0, NORTH), (1, 0, SOUTH), (0, -1, WEST), (0, 1, EAST))  # (dy, dx, 该边有墙时的编码)


def label_rooms(grid: list[list[int]], n: int, m: int) -> tuple[list[int], list[int]]:
    """洪水填充：返回 (每个格子的房间号, 每个房间的格子数)。"""
    room, sizes = [-1] * (n * m), []
    for start in range(n * m):
        if room[start] >= 0:
            continue
        rid = len(sizes)           # 房间号就是它被发现的顺序，同时也能当 sizes 的下标
        room[start], stack, size = rid, [start], 0
        while stack:               # 显式栈，避免格子连成蛇形时递归过深
            y, x = divmod(stack.pop(), m)
            size += 1
            v = grid[y][x]
            for dy, dx, wall in AROUND:
                ny, nx = y + dy, x + dx
                if not (0 <= ny < n and 0 <= nx < m):
                    continue           # 邻居在城堡外
                if v & wall or room[ny * m + nx] >= 0:
                    continue           # 这条边有墙，或邻居已经归属某个房间
                room[ny * m + nx] = rid
                stack.append(ny * m + nx)
        sizes.append(size)
    return room, sizes


def removable_walls(room: list[int], sizes: list[int], n: int, m: int) -> Iterator[tuple[int, int, int, str]]:
    """产出每一面可拆的墙：(合并后的房间大小, -2x, 2y, 墙名)，其中 (x, y) 是墙的中点。

    洪水填充顺着无墙边扩散，所以相邻两格房间号不同就说明中间隔着墙（反之不成立：
    房间内部可能还立着多余的墙，拆它不会让房间变大，跳过即可）。
    竖墙（E）用西侧格子命名，横墙（N）用南侧格子命名；中点坐标都乘 2 是为了把半整数变成整数。
    """
    for y in range(n):
        for x in range(m):
            here = room[y * m + x]
            if x + 1 < m and room[y * m + x + 1] != here:      # 拆竖墙：东西两间房合并
                merged = sizes[here] + sizes[room[y * m + x + 1]]
                yield merged, -(2 * x + 2), 2 * y + 1, f"{y + 1} {x + 1} E"
            if y + 1 < n and room[(y + 1) * m + x] != here:    # 拆横墙：南北两间房合并
                merged = sizes[here] + sizes[room[(y + 1) * m + x]]
                yield merged, -(2 * x + 1), 2 * y + 2, f"{y + 2} {x + 1} N"


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    m, n = next(data), next(data)  # 先给列数 M，再给行数 N
    grid = [[next(data) for _ in range(m)] for _ in range(n)]

    room, sizes = label_rooms(grid, n, m)
    # 元组的字典序比较天然实现了题面的三级规则：合并大小 → 中点越靠西 → 中点越靠南
    merged, _neg2x, _y2, name = max(removable_walls(room, sizes, n, m))

    print(len(sizes))
    print(max(sizes))
    print(merged)
    print(name)


if __name__ == "__main__":
    solve()
