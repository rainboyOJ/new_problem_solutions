#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-11 22:00
# update_at: 2026-07-11 22:00

import sys

NEG = -10**18


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    a = [0] + [next(data) for _ in range(n)]          # 1-indexed 地雷数
    g = [[] for _ in range(n + 1)]
    while True:
        x, y = next(data), next(data)
        if x == 0 and y == 0:
            break
        g[x].append(y)

    dp = [0] * (n + 1)                                # 从 i 出发能挖到的最多地雷
    nxt = [0] * (n + 1)                               # 最优路径的下一个点，0 表示结束
    for u in range(n, 0, -1):
        best, nxt_u = NEG, 0
        for v in g[u]:
            if dp[v] > best:
                best, nxt_u = dp[v], v
        dp[u] = a[u] + (best if best != NEG else 0)
        nxt[u] = nxt_u

    start = max(range(1, n + 1), key=lambda i: dp[i])  # 全局最优起点
    path: list[str] = []
    u = start
    while u:
        path.append(str(u))
        u = nxt[u]

    print('-'.join(path))
    print(dp[start])


if __name__ == "__main__":
    solve()
