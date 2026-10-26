#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-26 13:40
# update_at: 2026-10-26 13:40

import sys

NEG = None  # 哨兵：状态不可达（本行该位置到不了）


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, k = next(data), next(data)

    tri: list[list[int]] = []  # tri[i-1] 是第 i 行（下标 0 起）
    for i in range(n):
        tri.append([next(data) for _ in range(i + 1)])

    # 一条路径只经过 n 个格子，用不完 n 次以上的乘 3 机会
    limit = k if k < n else n

    # prev[j][c]：走到上一行第 j 列（0 起）、已乘 3 共 c 次的最大得分；NEG 表示不可达
    prev: list[list[int | None]] = [[NEG] * (limit + 1) for _ in range(n)]
    prev[0][0] = tri[0][0]
    if limit >= 1:
        prev[0][1] = tri[0][0] * 3

    for i in range(1, n):  # 第 i+1 行，本行列号 0..i
        width = limit + 1
        cur: list[list[int | None]] = [[NEG] * width for _ in range(i + 1)]
        for j in range(i + 1):
            row = cur[j]
            for c in range(width):
                # 不乘 3：前驱 (j) 与 (j-1)，各自恰好用了 c 次
                best = prev[j][c] if j < i else NEG
                left = prev[j - 1][c] if j >= 1 else NEG
                pick = best if best is not None and (left is None or best >= left) else left
                if pick is not None:
                    row[c] = pick + tri[i][j]
                # 乘 3：前驱要求上一行恰好用了 c-1 次
                if c >= 1:
                    best2 = prev[j][c - 1] if j < i else NEG
                    left2 = prev[j - 1][c - 1] if j >= 1 else NEG
                    pick2 = best2 if best2 is not None and (left2 is None or best2 >= left2) else left2
                    if pick2 is not None:
                        value = pick2 + tri[i][j] * 3
                        if row[c] is None or value > row[c]:
                            row[c] = value
        prev = cur

    reachable = [value for row in prev for value in row if value is not None]
    print(max(reachable))


if __name__ == "__main__":
    solve()
