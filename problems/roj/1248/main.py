#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 01:36
# update_at: 2026-09-30 01:36

import sys

WALL = ord('#')  # 网格里存的是字节值，'#' 的字节值是 35，不可通行单元的判据
START, EXIT = ord('S'), ord('E')

# 六个方向的 (层, 行, 列) 偏移：层 ±1 是上下，行 ±1 是前后，列 ±1 是左右
DIRS: tuple[tuple[int, int, int], ...] = (
    (1, 0, 0), (-1, 0, 0), (0, 1, 0), (0, -1, 0), (0, 0, 1), (0, 0, -1)
)


def find(dungeon: list[list[bytes]], key: int) -> tuple[int, int, int]:
    """定位标记字符 key（S 或 E）所在的 (层, 行, 列)；题面保证它出现且只出现一次。"""
    return next(
        (l, r, c)
        for l, layer in enumerate(dungeon)
        for r, row in enumerate(layer)
        for c in range(len(row))
        if row[c] == key
    )


def escape_minutes(
    dungeon: list[list[bytes]], start: tuple[int, int, int], target: tuple[int, int, int]
) -> int | None:
    """六方向 BFS 逐层扩展，返回 start→target 的最少分钟数；不可达返回 None。"""
    L, R, C = len(dungeon), len(dungeon[0]), len(dungeon[0][0])
    seen = {start}
    frontier = [start]  # 恰好用 minutes 分钟能站到的所有格子
    minutes = 0
    while frontier:
        nxt: list[tuple[int, int, int]] = []  # 再多走一分钟能站到的格子
        for l, r, c in frontier:
            if (l, r, c) == target:
                return minutes
            for dl, dr, dc in DIRS:
                nl, nr, nc = l + dl, r + dr, c + dc
                in_range = 0 <= nl < L and 0 <= nr < R and 0 <= nc < C  # 先判界，避免越界读
                can_step = in_range and dungeon[nl][nr][nc] != WALL and (nl, nr, nc) not in seen
                if can_step:
                    seen.add((nl, nr, nc))  # 入队即标记，同一个格子不会重复扩展
                    nxt.append((nl, nr, nc))
        frontier, minutes = nxt, minutes + 1
    return None


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    out: list[str] = []

    while True:
        L, R, C = int(next(data)), int(next(data)), int(next(data))
        if L == 0 and R == 0 and C == 0:  # 三个 0 表示输入结束
            break
        # 每层 R 行、每行 C 个字符；层与层之间的空行被 read().split() 当作空白丢掉
        dungeon = [[next(data) for _ in range(R)] for _ in range(L)]

        minutes = escape_minutes(dungeon, find(dungeon, START), find(dungeon, EXIT))
        out.append(f"Escaped in {minutes} minute(s)." if minutes is not None else "Trapped!")

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
