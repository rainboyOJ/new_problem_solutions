#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 02:15
# update_at: 2026-09-30 02:15

import sys


def solve() -> None:
    """自底向上滚动一维数组：best[c] 表示"从当前行第 c 列出发到底部"的最大路径和。"""
    data = iter(map(int, sys.stdin.buffer.read().split()))
    R = next(data)
    rows = [[next(data) for _ in range(i + 1)] for i in range(R)]  # 第 i 行有 i+1 个数

    best = rows[-1]  # 最后一行的点只能停在原地，出发和就是它自己
    for row in reversed(rows[:-1]):
        # 第 c 列只能走向正下方的 c 或右下方的 c+1，继承两支里较大的那个
        best = [v + max(best[c], best[c + 1]) for c, v in enumerate(row)]

    print(best[0])


if __name__ == "__main__":
    solve()
