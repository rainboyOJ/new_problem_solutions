#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 23:15
# update_at: 2026-10-08 23:15

import sys

GAIN = 10  # 两条对角线上的元素统一加 10


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data, 0)
    if n == 0:
        return

    matrix = [[next(data) for _ in range(n)] for _ in range(n)]

    # 主对角线 (i, i)，副对角线 (i, n-1-i)。用单条件三元代替「先两轮循环各自累加」，
    # 天然不存在重复路径：n 为奇数时中心格虽同时落在两条对角线上，仍只加一次 10。
    out = [' '.join(str(value + (GAIN if i == j or i + j == n - 1 else 0))
                    for j, value in enumerate(row))
           for i, row in enumerate(matrix)]
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
