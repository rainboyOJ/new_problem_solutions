#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 15:14
# update_at: 2026-10-01 15:14

from collections import deque

# 八个方向的位移：水平、垂直加上四条对角线
DELTA = ((-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1))


def solve() -> None:
    it = iter(map(int, input().split()))
    x, y, mx, my = next(it), next(it), next(it), next(it)

    # 地图按输入顺序存第 y 行，grid[ny-1] 对应坐标里的第 ny 行
    grid = [input().rstrip() for _ in range(y)]

    # dist 记录每个格子的占领星期数，未访问为 -1；石头永不入队
    dist = [[-1] * x for _ in range(y)]

    def spread(queue: deque) -> None:
        """BFS 一层一层扩散，队头出队的星期数就是该格被占领的最早时间。"""
        while queue:
            ny, nx, week = queue.popleft()
            for dy, dx in DELTA:
                fy, fx = ny + dy, nx + dx
                in_map = 0 <= fy < y and 0 <= fx < x
                if in_map and grid[fy][fx] == "." and dist[fy][fx] == -1:
                    dist[fy][fx] = week + 1
                    queue.append((fy, fx, week + 1))

    dist[my - 1][mx - 1] = 0
    spread(deque([(my - 1, mx - 1, 0)]))

    # 石头的 -1 不影响最大值，答案就是所有格子的最晚占领时间
    print(max(max(row) for row in dist))


if __name__ == "__main__":
    solve()
