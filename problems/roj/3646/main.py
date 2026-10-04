#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 12:33
# update_at: 2026-10-02 12:33

import heapq
import sys

INF = 10 ** 9
DIRS = ((-1, 0), (1, 0), (0, -1), (0, 1))  # 上、下、左、右

# Dijkstra 状态：(x, y, 是否站在魔法格, 脚下颜色)。
# magic=0 站在原本有色的格子，脚下颜色固定；magic=1 站在被魔法染色的无色格，
# 颜色取施法时脚下格子的颜色（这样入场不额外花钱）。
State = tuple[int, int, int, int]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    m, n = next(data), next(data)
    cells = [(next(data), next(data), next(data)) for _ in range(n)]  # (x, y, c)
    color = {(x, y): c for x, y, c in cells}  # 原本有色的格子 → 颜色

    start: State = (1, 1, 0, color[1, 1])
    dist: dict[State, int] = {start: 0}
    pq = [(0, start)]
    ans = -1

    while pq:
        d, state = heapq.heappop(pq)
        if d != dist[state]:  # 过期的堆元素
            continue
        x, y, magic, c = state
        if (x, y) == (m, m):  # Dijkstra 先弹出的终点状态就是最优解
            ans = d
            break
        for dx, dy in DIRS:
            nx, ny = x + dx, y + dy
            if not (1 <= nx <= m and 1 <= ny <= m):
                continue
            nc = color.get((nx, ny))
            if nc is not None:  # 落到有色格：同色 0 金币，异色 1 金币
                nd, ns = d + (nc != c), (nx, ny, 0, nc)
            elif magic:  # 魔法不能连续使用，站在魔法格上只能落回有色格
                continue
            else:  # 施法：花 2 金币把无色格染成脚下颜色再走上去
                nd, ns = d + 2, (nx, ny, 1, c)
            if nd < dist.get(ns, INF):
                dist[ns] = nd
                heapq.heappush(pq, (nd, ns))

    print(ans)


if __name__ == "__main__":
    solve()
