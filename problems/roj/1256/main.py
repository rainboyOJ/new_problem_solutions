#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys
from collections import deque


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    it = iter(data)
    T = int(next(it))
    out: list[str] = []

    for _ in range(T):
        R = int(next(it))
        C = int(next(it))
        grid = [list(next(it).decode()) for _ in range(R)]

        # 定位起点 S 与终点 E
        for r in range(R):
            for c in range(C):
                if grid[r][c] == 'S':
                    sr, sc = r, c
                elif grid[r][c] == 'E':
                    tr, tc = r, c

        dist = [[-1] * C for _ in range(R)]
        dist[sr][sc] = 0
        q = deque([(sr, sc)])

        while q:
            r, c = q.popleft()
            if (r, c) == (tr, tc):
                break
            d = dist[r][c] + 1
            for nr, nc in ((r - 1, c), (r + 1, c), (r, c - 1), (r, c + 1)):
                if 0 <= nr < R and 0 <= nc < C and grid[nr][nc] != '#' and dist[nr][nc] == -1:
                    dist[nr][nc] = d
                    q.append((nr, nc))

        out.append(str(dist[tr][tc]) if dist[tr][tc] != -1 else 'oop!')

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
