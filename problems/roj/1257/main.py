#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 02:01
# update_at: 2026-10-14 12:00

import sys
from collections import deque

# 马走日的 8 个偏移：|dr| + |dc| == 3 且两分量都非零，恰好是 (±1, ±2) 与 (±2, ±1)
DIRS = [(dr, dc) for dr in (-2, -1, 1, 2) for dc in (-2, -1, 1, 2) if abs(dr) + abs(dc) == 3]  # 8 个马步


def min_knight_steps(size: int, start: tuple[int, int], target: tuple[int, int]) -> int:
    """BFS 求马从 start 到 target 的最少步数；起止相同返回 0。"""
    if start == target:
        return 0
    dist = {start: 0}                 # tuple 坐标直接当 key，既是距离表也是访问标记
    queue = deque([start])
    while queue:
        r, c = queue.popleft()
        step = dist[r, c] + 1         # 出队点的下一层步数
        for dr, dc in DIRS:
            nr, nc = r + dr, c + dc
            if 0 <= nr < size and 0 <= nc < size and (nr, nc) not in dist:
                if (nr, nc) == target:
                    return step       # BFS 首次到达即最短
                dist[nr, nc] = step
                queue.append((nr, nc))
    return -1                         # 棋盘够大时马必可达，此处仅兜底


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)

    for _ in range(T):
        size = next(data)                                # 棋盘边长 L
        start = (next(data), next(data))                 # 起点 (x, y)
        target = (next(data), next(data))                # 终点 (x, y)
        out.append(str(min_knight_steps(size, start, target)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
