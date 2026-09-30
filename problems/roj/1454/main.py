#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 11:45
# update_at: 2026-09-30 11:45

import sys
from collections import deque

# 8 邻接方向：题面把「有公共顶点」也算相邻，所以含 4 条对角线
DIRS = ((-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1))


def explore(grid: list[list[int]], seen: list[bytearray], start: tuple[int, int]) -> tuple[bool, bool]:
    """从 start 洪泛一个「高度全相同且 8 连通」的块。

    返回值是 (是否山峰, 是否山谷)：山峰要求周围都比它矮，山谷要求周围都比它高，
    所以「有比它高的」就不可能是山峰，「有比它矮的」就不可能是山谷。
    整个地图高度相同时两侧都不会被排除，两种身份同时成立。
    """
    n = len(grid)
    height = grid[start[0]][start[1]]
    has_lower = has_higher = False
    queue = deque([start])
    seen[start[0]][start[1]] = 1

    while queue:
        r, c = queue.popleft()
        for dr, dc in DIRS:
            nr, nc = r + dr, c + dc
            if not (0 <= nr < n and 0 <= nc < n):  # 出界：不是格子，不参与比较
                continue
            if grid[nr][nc] == height:
                if not seen[nr][nc]:               # 同高且未访问：并入当前块
                    seen[nr][nc] = 1
                    queue.append((nr, nc))
            elif grid[nr][nc] < height:            # 块外邻居：定身份用，不入队
                has_lower = True
            else:
                has_higher = True

    return not has_higher, not has_lower


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    grid = [[next(data) for _ in range(n)] for _ in range(n)]

    seen = [bytearray(n) for _ in range(n)]  # seen[r][c]=1 表示该格已被归入某个块
    peaks = valleys = 0

    for r in range(n):
        for c in range(n):
            if not seen[r][c]:
                is_peak, is_valley = explore(grid, seen, (r, c))
                peaks += is_peak                 # bool 相加等价于 if ... : ans += 1
                valleys += is_valley

    print(peaks, valleys)


if __name__ == "__main__":
    solve()
