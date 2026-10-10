#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 15:29
# update_at: 2026-10-07 15:29

import heapq
import sys

INF = 1 << 62  # 哨兵：这个格子的逃逸水位还没被任何一条通往外围的路径确定

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Grid = list[list[int]]  # 地形高度或逃逸水位，Grid[i][j] 是第 i 行第 j 列


def escape_levels(n: int, m: int, height: Grid) -> Grid:
    """回答「每个格子逃到外围时水位最高要被抬到哪里」：所有路径中「路径最大地形高度」的最小值。"""
    level: Grid = [[INF] * m for _ in range(n)]
    heap = []  # 小根堆：(水位, 行, 列)
    for i in range(n):
        for j in range(m):
            if i in (0, n - 1) or j in (0, m - 1):  # 边界格子直接挨着高度 0 的外围
                level[i][j] = max(height[i][j], 0)
                heap.append((level[i][j], i, j))
    heapq.heapify(heap)

    while heap:
        d, i, j = heapq.heappop(heap)
        if d > level[i][j]:
            continue  # 过期堆项：这个格子已经被更小的水位定型过
        for ni, nj in ((i - 1, j), (i + 1, j), (i, j - 1), (i, j + 1)):
            if 0 <= ni < n and 0 <= nj < m:
                nd = max(d, height[ni][nj])  # 走这条边，水位被沿途更高的地形顶起来
                if nd < level[ni][nj]:
                    level[ni][nj] = nd
                    heapq.heappush(heap, (nd, ni, nj))
    return level


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    if n == 0 or m == 0:  # 一块地都没有，没有输出
        return
    height = [[next(data) for _ in range(m)] for _ in range(n)]
    level = escape_levels(n, m, height)
    # 积水高度 = 逃逸水位 - 地形高度，恒非负
    print('\n'.join(' '.join(str(level[i][j] - height[i][j]) for j in range(m)) for i in range(n)))


if __name__ == "__main__":
    solve()
