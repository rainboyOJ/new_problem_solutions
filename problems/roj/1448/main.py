#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 11:11
# update_at: 2026-09-30 11:32

import sys
from collections import deque

BACKSLASH = ord('\\')  # 反斜杠元件：导线连通「左上—右下」一对顶点
SLASH = ord('/')       # 斜杠元件：导线连通「右上—左下」一对顶点

# 从格点斜着跨过一块元件到达对角格点，需要该元件是哪种方向。
# 每项 = (行偏移, 列偏移, 直通所需的方向)；跨过的元件总是位于 (min(行), min(列))。
STEPS = (
    (-1, -1, BACKSLASH),  # 左上：走元件的「右下」半条线
    (1, 1, BACKSLASH),    # 右下：走元件的「左上」半条线
    (-1, 1, SLASH),       # 右上：走元件的「左下」半条线
    (1, -1, SLASH),       # 左下：走元件的「右上」半条线
)


def light_up(grid: list[bytes], n: int, m: int) -> int:
    """返回点亮灯泡所需的最少旋转次数，无解返回 -1。

    图上的点 = 电路板的 (N+1)×(M+1) 个格点，边 = 斜着跨过一块元件到对角格点。
    若元件方向正好能穿过，边权 0；否则要把它转 90°，边权 1。于是问题变成 0-1 BFS。
    """
    dist = [[-1] * (m + 1) for _ in range(n + 1)]  # -1 表示尚未到达该格点
    dist[0][0] = 0
    queue = deque([(0, 0)])

    while queue:
        r, c = queue.popleft()
        d = dist[r][c]
        if (r, c) == (n, m):  # 0-1 BFS 出队即最短路，第一次弹出终点就是答案
            return d
        for dr, dc, need in STEPS:
            nr, nc = r + dr, c + dc
            if not (0 <= nr <= n and 0 <= nc <= m):
                continue  # 目标格点越界
            # 跨过的元件就是两个格点围成的那个格子：行列各取小的那个
            cost = d + (grid[min(r, nr)][min(c, nc)] != need)  # 方向不符要转一次
            if dist[nr][nc] < 0 or cost < dist[nr][nc]:
                dist[nr][nc] = cost
                # 边权 0 走队头、边权 1 走队尾，队列始终按 dist 非递减排列
                (queue.appendleft if cost == d else queue.append)((nr, nc))

    return -1  # 队列空了还没弹出终点，说明电源与灯泡不连通


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n = int(next(data))
    m = int(next(data))
    grid = [next(data) for _ in range(n)]  # 每行一个 bytes，逐字节比较方向更快
    ans = light_up(grid, n, m)
    print('NO SOLUTION' if ans < 0 else ans)


if __name__ == "__main__":
    solve()
