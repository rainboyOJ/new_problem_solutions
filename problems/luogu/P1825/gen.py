#!/usr/bin/env python3
"""生成 P1825 Corn Maze S 小数据：随机小迷宫 + 成对大写字母传送门，规模适合暴力对拍。"""
import random

random.seed()

WALL_RATE = 0.2


def main():
    n = random.randint(2, 8)
    m = random.randint(2, 8)

    # 随机放墙，其余为草地
    grid = [["."] * m for _ in range(n)]
    for i in range(n):
        for j in range(m):
            if random.random() < WALL_RATE:
                grid[i][j] = "#"

    # 保证至少留 6 个空地：起点、终点 + 最多两对传送门；
    # 墙不足时从打乱的墙列表中逐个打开，避免死循环
    empty = [(i, j) for i in range(n) for j in range(m) if grid[i][j] == "."]
    walls = [(i, j) for i in range(n) for j in range(m) if grid[i][j] == "#"]
    random.shuffle(walls)
    for i, j in walls[: max(0, 6 - len(empty))]:
        grid[i][j] = "."
        empty.append((i, j))

    random.shuffle(empty)

    # 起点与终点
    sx, sy = empty.pop()
    ex, ey = empty.pop()
    grid[sx][sy] = "@"
    grid[ex][ey] = "="

    # 随机 0..3 对传送门，每对使用同一个大写字母
    letter_num = random.randint(0, 3)
    for ch in random.sample("ABCDEFGHIJKLMNOPQRSTUVWXYZ", letter_num):
        if len(empty) < 2:
            break
        x1, y1 = empty.pop()
        x2, y2 = empty.pop()
        grid[x1][y1] = ch
        grid[x2][y2] = ch

    print(n, m)
    for row in grid:
        print("".join(row))


if __name__ == "__main__":
    main()
