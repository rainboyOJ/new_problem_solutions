#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys
from collections import deque

# 一对相邻格子编码为两个 16 位掩码：状态与这两格异或即完成一次交换
ADJ = (
    [1 << (r * 4 + c) | 1 << (r * 4 + c + 1) for r in range(4) for c in range(3)]  # 横向 12 对
    + [1 << (r * 4 + c) | 1 << ((r + 1) * 4 + c) for r in range(3) for c in range(4)]  # 纵向 12 对
)


def solve() -> None:
    tokens = sys.stdin.read().split()  # 4 行棋盘 + 4 行棋盘，每行恰 4 个 token
    read_board = lambda lo: int(''.join(tokens[lo:lo + 4]), 2)  # 4 行 01 拼成一个 16 位掩码
    start, target = read_board(0), read_board(4)

    dist = {start: 0}  # start 出发的最短步数
    q = deque([start])
    while q and target not in dist:
        u = q.popleft()
        for pair in ADJ:
            if u & pair in (0, pair):
                continue             # 两格同色，交换后局面不变
            v = u ^ pair             # 两格异色，交换 = 两位置同时翻转
            if v not in dist:
                dist[v] = dist[u] + 1
                q.append(v)

    print(dist[target])


if __name__ == "__main__":
    solve()
