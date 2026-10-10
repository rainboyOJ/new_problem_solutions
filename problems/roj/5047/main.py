#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 20:40
# update_at: 2026-10-08 20:40

import sys

# 四个方向的增量，按「下、左、上、右」顺时针循环，与 C++ 版一致
DX = (1, 0, -1, 0)
DY = (0, -1, 0, 1)


def spiral(n: int) -> list[list[int]]:
    """从右上角起笔，按「下、左、上、右」螺旋填入 1..n*n，返回 n×n 方阵。"""
    a = [[0] * n for _ in range(n)]
    x, y, d = 0, n - 1, 0  # 起点为右上角 (0, n-1)，方向 0 即先向下
    for v in range(1, n * n + 1):
        a[x][y] = v
        nx, ny = x + DX[d], y + DY[d]  # 先看后走：越界或已填过就顺时针转一次
        if not (0 <= nx < n and 0 <= ny < n) or a[nx][ny]:
            d = (d + 1) % 4
            nx, ny = x + DX[d], y + DY[d]
        x, y = nx, ny
    return a


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    sys.stdout.write(''.join(' '.join(map(str, row)) + '\n' for row in spiral(n)))


if __name__ == '__main__':
    solve()
