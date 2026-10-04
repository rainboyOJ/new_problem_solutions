#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 02:14
# update_at: 2026-09-30 02:21

import sys
from collections import deque


def shortest_time(n: int, k: int) -> int:
    """农夫从 n 到 k 的最少分钟数：边权全为 1 的最短路 = BFS 第一次到达。"""
    if k <= n:
        # 每步向下最多减 1（+1 与 ×2 都不降），t 步后位置 ≥ n-t，
        # 故到 k 至少需 n-k 步；一路 -1 恰好达到。
        return n - k
    limit = 2 * k  # 上界：越过 2K 的位置 x 回到 K 至少要 x-K>K 步，不如直线走法的 k-n 步
    dist = [-1] * (limit + 1)  # -1 兼作"未访问"标记
    dist[n] = 0
    frontier = deque([n])
    while frontier:
        x = frontier.popleft()
        for y in (x - 1, x + 1, 2 * x):
            if 0 <= y <= limit and dist[y] < 0:
                dist[y] = dist[x] + 1
                if y == k:
                    return dist[y]  # 逐层扩展，首次到达即最少分钟数
                frontier.append(y)
    return dist[k]


def solve() -> None:
    n, k = map(int, sys.stdin.buffer.read().split())
    print(shortest_time(n, k))


if __name__ == "__main__":
    solve()
