#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 01:46
# update_at: 2026-09-30 01:46

import sys

# 四个方向的 (行增量, 列增量, 该方向的墙位)：北墙 2 挡住往上，南墙 8 挡住往下，
# 西墙 1 挡住往左，东墙 4 挡住往右。位值是题面给定的，不能改顺序含义。
DIRS: tuple[tuple[int, int, int], ...] = ((-1, 0, 2), (1, 0, 8), (0, -1, 1), (0, 1, 4))


def room_sizes(m: int, n: int, wall: list[list[int]]) -> list[int]:
    """返回每个房间的面积（方块数）：对每个未访问格做一次洪水填充。

    格子编号 id = r * n + c，邻居能否过去只看当前格自己那一侧的墙位——
    因为室内的墙被相邻两格各定义一次，只查一侧就足够了，不必两侧都查。
    """
    seen = bytearray(m * n)
    sizes: list[int] = []
    for start in range(m * n):
        if seen[start]:
            continue
        seen[start] = 1                       # 入栈即标记，每个格子只被展开一次
        stack = [start]
        size = 0
        while stack:
            size += 1
            r, c = divmod(stack.pop(), n)
            for dr, dc, bit in DIRS:
                nr, nc = r + dr, c + dc
                in_range = 0 <= nr < m and 0 <= nc < n   # 先判界，避免读到别的行
                can_step = in_range and not wall[r][c] & bit and not seen[nr * n + nc]
                if can_step:
                    seen[nr * n + nc] = 1
                    stack.append(nr * n + nc)
        sizes.append(size)
    return sizes


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    m, n = next(data), next(data)             # 行数（南北）在前，列数（东西）在后
    wall = [[next(data) for _ in range(n)] for _ in range(m)]

    sizes = room_sizes(m, n, wall)
    print(f"{len(sizes)}\n{max(sizes)}")       # 题面保证至少两个房间，max 不会空


if __name__ == "__main__":
    solve()
