#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 04:33
# update_at: 2026-10-01 04:45

import sys
from collections import deque

SPACE = ' '  # 空格这一个字符同时表示三种东西：格点、格间通道、栅栏之外


def build_grid(w: int, h: int, lines: list[str]) -> list[str]:
    """把 2*h+1 行的迷宫补成 (2*h+3) x (2*w+3)，四周各包一圈空白。

    有了这圈空白，所有空区域（通道 + 迷宫外的自由空间）直接连通；两段出口
    栅栏是迷宫边缘上仅有的字符缺口，也就成了通道通向自由的唯一两个孔。
    补行长度时多留一个字符，长度不足的输入行（USACO 原数据会去掉行尾空格）
    也能被 ljust 补齐而不越界。
    """
    width = 2 * w + 3
    return ([' ' * width]
            + [' ' + line.ljust(width - 2) + ' ' for line in lines[:2 * h + 1]]
            + [' ' * width])


def flood_dist(grid: list[str]) -> list[int]:
    """从迷宫外做一次多源 BFS（洪水填充），返回每个字符位的距离。

    距离按"字符位移次数"计：相邻两个字符位算 1 步。牛走一格 = 跨过 2 个字符位，
    所以格子层数 = 该格子格心的字符距离 / 2，具体换算放在 solve 里做。
    """
    width, height = len(grid[0]), len(grid)
    dist = [-1] * (width * height)
    queue = deque()

    # 补出来的最外圈整体入队当超级源点：它们就是迷宫外的那片自由空间，距离为 0。
    for v in range(width * height):
        r, c = divmod(v, width)
        if r in (0, height - 1) or c in (0, width - 1):
            dist[v] = 0
            queue.append(v)

    while queue:
        v = queue.popleft()
        r, c = divmod(v, width)
        for nr, nc in ((r - 1, c), (r + 1, c), (r, c - 1), (r, c + 1)):
            if 0 <= nr < height and 0 <= nc < width and grid[nr][nc] == SPACE and dist[nr * width + nc] < 0:
                dist[nr * width + nc] = dist[v] + 1
                queue.append(nr * width + nc)
    return dist


def solve() -> None:
    data = sys.stdin.buffer.read().decode().splitlines()
    w, h = map(int, data[0].split())

    grid = build_grid(w, h, data[1:2 * h + 2])
    width = 2 * w + 3
    dist = flood_dist(grid)

    # 格子 (r, c) 的格心在补齐网格里的位置是 (2r+2, 2c+2)。格心的字符距离恰好等于
    # 该格子到最近出口的步数的两倍（每走一步正好跨 2 个字符位，且最短路会成对地
    # 经历"通道中点 → 格心"），所以对所有格心取最大距离再整除 2 就是答案。
    ans = max(dist[(2 * r + 2) * width + 2 * c + 2] for r in range(h) for c in range(w)) // 2
    print(ans)


if __name__ == "__main__":
    solve()
