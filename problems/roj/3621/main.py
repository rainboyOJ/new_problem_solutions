#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 10:54
# update_at: 2026-10-02 10:54

import sys
from itertools import accumulate

N = 129  # 街道编号 0..128


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    d, n = data[0], data[1]

    # 权重网格：路口 (x, y) 上的公共场所数量（题目保证同一坐标只出现一次）
    g = [[0] * (N + 1) for _ in range(N + 1)]
    for i in range(n):
        x, y, k = data[2 + i * 3:5 + i * 3]
        g[x][y] = k

    # 二维前缀和：首行全 0 哨兵，逐行把行内前缀与上一行叠加
    # P[i][j] = sum(g[0..i-1][0..j-1])，比手工双重循环短得多
    P = [[0] * (N + 1)]
    for row in g:
        P.append([a + b for a, b in zip(accumulate(row, initial=0), P[-1])])

    best = cnt = 0
    # 枚举每个路口 (cx, cy) 作为发射器中心，正方形覆盖窗口用前缀和 O(1) 查询
    for cx in range(N):
        for cy in range(N):
            # 覆盖正方形与网格求交（正方形可越出城市，但所有路口都在网格内）
            x1, x2 = max(cx - d, 0), min(cx + d, N - 1)
            y1, y2 = max(cy - d, 0), min(cy + d, N - 1)
            s = P[x2 + 1][y2 + 1] - P[x1][y2 + 1] - P[x2 + 1][y1] + P[x1][y1]
            if s > best:
                best, cnt = s, 1
            elif s == best:
                cnt += 1
    print(cnt, best)


if __name__ == "__main__":
    solve()
