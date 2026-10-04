#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 19:50
# update_at: 2026-09-29 19:50

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)               # 行数、列数

    rows_a = [[next(data) for _ in range(m)] for _ in range(n)]  # 矩阵 A 的 n 行
    rows_b = [[next(data) for _ in range(m)] for _ in range(n)]  # 矩阵 B 的 n 行

    # 逐行 zip 出对应元素对，逐元素相加后按空格拼接
    out = [
        ' '.join(map(str, (x + y for x, y in zip(row_a, row_b))))  # 同一行同一列相加
        for row_a, row_b in zip(rows_a, rows_b)
    ]
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
