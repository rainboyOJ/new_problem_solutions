#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 21:30
# update_at: 2026-10-09 23:08
#
# ROJ 3194《Intervals 区间》：区间选点，前缀和转差分约束 + SPFA 最长路。
#   S_b - S_{a-1} >= c   => S_b >= S_{a-1} + c
#   S_x - S_{x-1} <= 1   => S_{x-1} >= S_x - 1
#   S_x - S_{x-1} >= 0   => S_x >= S_{x-1} + 0
# 答案 = 最长路终点值 dist[max_val]。
# 坐标整体 +1 规避 a_i = 0 时 a_i-1 = -1 的下标问题。

import sys
from collections import deque

NEG = -10 ** 9


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return

    # 首行有两种格式：题面「第一行 n」（1 个 token）与官方数据「上界 n」（2 个 token）。
    # 每个区间恒占 3 个 token，故由 token 总数的模 3 余数唯一判定（1+3n≡1、2+3n≡2）。
    n, head = (data[0], 1) if (len(data) - 1) % 3 == 0 else (data[1], 2)

    adj = [[] for _ in range(50005)]
    min_val, max_val = 50005, 0
    for i in range(n):
        a, b, c = data[head + 3 * i] + 1, data[head + 3 * i + 1] + 1, data[head + 3 * i + 2]
        adj[a - 1].append((b, c))
        min_val, max_val = min(min_val, a - 1), max(max_val, b)

    for i in range(min_val, max_val):
        adj[i].append((i + 1, 0))
        adj[i + 1].append((i, -1))

    dist = [NEG] * (max_val + 2)
    inq = [False] * (max_val + 2)
    dist[min_val] = 0
    q = deque([min_val])
    inq[min_val] = True
    while q:
        u = q.popleft()
        inq[u] = False
        du = dist[u]
        for v, w in adj[u]:
            if du + w > dist[v]:
                dist[v] = du + w
                if not inq[v]:
                    q.append(v)
                    inq[v] = True

    print(dist[max_val])


if __name__ == "__main__":
    solve()
