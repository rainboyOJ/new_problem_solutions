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


def board_of(row0: int, row1: int, row2: int, row3: int) -> int:
    """四行 01 数字各占 4 位、先读到的行占高位，拼成一个 16 位掩码。"""
    return row0 << 12 | row1 << 8 | row2 << 4 | row3


def solve() -> None:
    # 每行是 4 位 01 串（前导 0 有意义），按二进制解析；空行被 split 吞掉
    lines = sys.stdin.buffer.read().split()
    data = iter(int(line, 2) for line in lines)
    start = board_of(next(data), next(data), next(data), next(data))
    target = board_of(next(data), next(data), next(data), next(data))

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
