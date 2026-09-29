#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 05:33
# update_at: 2026-09-30 05:44

import sys
from collections import deque

BOARD = 100  # 棋盘 100×100，走法在两个轴上独立地取增量，正好写成 (行, 列) 两维
POINTS = 2   # 输入是黑马、白马两行坐标，两匹马的终点都是 (1, 1)

MOVES = tuple(  # 12 种走法：日字的 8 个 L 型，加上田字的 4 个对角
    [(dr * a, dc * b) for dr, dc in ((1, 2), (2, 1)) for a in (-1, 1) for b in (-1, 1)]  # 8
    + [(2 * a, 2 * b) for a in (-1, 1) for b in (-1, 1)]  # 4
)


def corner_distances() -> dict[tuple[int, int], int]:
    """棋盘上每个格子到 (1, 1) 的最少步数。

    两匹马都在 (1, 1) 收尾，所以从 (1, 1) 出发做一次 BFS，整张距离表两问共用。
    走法是 (行增量, 列增量) 的定长组合，且集合关于取负封闭（能走过去就能走回来），
    因此反向搜索得到的距离与正向完全一致。
    """
    dist = {(1, 1): 0}
    q = deque(dist)
    while q:
        point = q.popleft()
        for dr, dc in MOVES:
            nxt = (point[0] + dr, point[1] + dc)
            inside = 1 <= nxt[0] <= BOARD and 1 <= nxt[1] <= BOARD
            if inside and nxt not in dist:  # BFS 首次访问即最短路
                dist[nxt] = dist[point] + 1
                q.append(nxt)
    return dist


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    dist = corner_distances()
    # 输入就是两行坐标，黑马、白马各查一次表（同一个生成器按顺序取四个数）
    print('\n'.join(str(dist[(next(data), next(data))]) for _ in range(POINTS)))


if __name__ == "__main__":
    solve()
