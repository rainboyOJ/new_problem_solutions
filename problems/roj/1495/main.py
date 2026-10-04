#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 14:39
# update_at: 2026-09-30 14:44

import sys
from collections import deque

FREE = -1  # 格间编码：-1 = 未出现在输入里，即无门无墙，直接可走
WALL = 0   # 格间编码：0 = 不可逾越的墙


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m, p = next(data), next(data), next(data)

    # gate[(r, c, r2, c2)]：相邻两格之间的门类型。-1 自由通行，0 是墙，>=1 是第 g 类门。
    gate: dict[tuple[int, int, int, int], int] = {}
    k = next(data)
    for _ in range(k):
        r1, c1, r2, c2, g = next(data), next(data), next(data), next(data), next(data)
        gate[(r1, c1, r2, c2)] = gate[(r2, c2, r1, c1)] = g  # 门是双向的，两个方向都登记

    # keys[r][c]：该格钥匙集合的位掩码；一把都没有时为 0。
    keys = [[0] * (m + 1) for _ in range(n + 1)]
    s = next(data)
    for _ in range(s):
        x, y, q = next(data), next(data), next(data)
        keys[x][y] |= 1 << (q - 1)  # 同类钥匙重复无意义，用或运算合并

    # 状态 (r, c, mask) = 站在 (r, c) 且已持有钥匙集合 mask。
    # 每格钥匙一到达就自动收进 mask，mask 只增不减，所以状态图无环，BFS 分层即可。
    start = keys[1][1]
    dist = {(1, 1, start): 0}
    queue = deque([(1, 1, start)])

    while queue:
        r, c, mask = queue.popleft()
        if (r, c) == (n, m):  # 队列按距离递增出队，首次弹出终点即最短时间
            print(dist[(r, c, mask)])
            return
        step = dist[(r, c, mask)] + 1
        for r2, c2 in ((r - 1, c), (r + 1, c), (r, c - 1), (r, c + 1)):
            if not (1 <= r2 <= n and 1 <= c2 <= m):
                continue
            g = gate.get((r, c, r2, c2), FREE)
            if g == WALL:
                continue                                    # 墙永远不可逾越
            opened = g == FREE or mask >> (g - 1) & 1       # 门要有对应钥匙才能穿
            nxt = (r2, c2, mask | keys[r2][c2])             # 落脚即拾取该格钥匙
            if opened and nxt not in dist:
                dist[nxt] = step
                queue.append(nxt)

    print(-1)  # 状态空间全部搜完仍未到达 (n, m)


if __name__ == "__main__":
    solve()
