#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 11:11
# update_at: 2026-09-30 11:11

import sys
from collections import deque
from functools import cache

KNIGHT_DELTAS = ((1, 2), (2, 1), (2, -1), (1, -2), (-1, -2), (-2, -1), (-2, 1), (-1, 2))  # 马步 8 个方向


@cache
def knight_graph(L: int) -> tuple[tuple[int, ...], ...]:
    """L×L 棋盘的马步邻接表：格子按 (x, y) → x*L+y 展平编号。

    同一组询问共享同一个 L，邻接表只建一次，之后每次 BFS 直接走表。
    """
    return tuple(
        tuple(
            (x + dx) * L + y + dy
            for dx, dy in KNIGHT_DELTAS
            if 0 <= x + dx < L and 0 <= y + dy < L  # 落在棋盘外的不建边
        )
        for x in range(L)
        for y in range(L)
    )


def knight_steps(L: int, start: int, target: int) -> int:
    """展平下标 start 到 target 的最少马步数；逐层 BFS，首次碰到 target 即最短。"""
    if start == target:
        return 0
    dist = [-1] * (L * L)  # -1 = 还没访问过
    dist[start] = 0
    queue = deque([start])
    while queue:
        pos = queue.popleft()
        step = dist[pos] + 1
        for nxt in knight_graph(L)[pos]:
            if dist[nxt] < 0:
                if nxt == target:  # BFS 按层扩展，第一次到达就是最少步数
                    return step
                dist[nxt] = step
                queue.append(nxt)
    return -1  # L≥4 的完整棋盘马步图连通，不会走到这里


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)  # 骑士数量
    out = []
    for _ in range(n):
        L = next(data)  # 棋盘边长
        sx, sy, tx, ty = next(data), next(data), next(data), next(data)
        out.append(str(knight_steps(L, sx * L + sy, tx * L + ty)))
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
