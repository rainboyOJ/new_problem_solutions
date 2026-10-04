#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 19:50
# update_at: 2026-09-29 20:01

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    m, n = next(data), next(data)
    grid = list(data)                          # 剩下全部 token：行优先展平的 m 行 n 列元素

    # 边缘和 = 全部元素和 - 内部元素和。内部格子是第 1..m-2 行（0 起编号）各去掉
    # 首尾两列后的连续段；m <= 2 或 n <= 2 时这段为空，减法自动退化成整矩阵求和。
    inner_sum = sum(
        sum(grid[r * n + 1: (r + 1) * n - 1])  # 第 r 行：跳过第 1 列，切到最后 1 列之前
        for r in range(1, m - 1)               # 内部行，0 起编号的首尾两行不在其中
    )
    print(sum(grid) - inner_sum)


if __name__ == "__main__":
    solve()
