#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 23:33
# update_at: 2026-09-30 23:33

import sys


def matrix_multiply(a: list[list[int]], b: list[list[int]], n: int, m: int, p: int) -> list[list[int]]:
    """计算 n×m 矩阵 A 与 m×p 矩阵 B 的乘积，返回 n×p 结果矩阵。"""
    # 转置 B 为 p×m，方便按行向量点积
    b_cols = [[b[k][j] for k in range(m)] for j in range(p)]
    return [
        [sum(a[i][k] * b_cols[j][k] for k in range(m)) for j in range(p)]
        for i in range(n)
    ]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))

    try:
        n = next(data)
    except StopIteration:
        return
    m = next(data)

    a = [[next(data) for _ in range(m)] for _ in range(n)]
    p = next(data)
    b = [[next(data) for _ in range(p)] for _ in range(m)]

    c = matrix_multiply(a, b, n, m, p)
    for row in c:
        print(*(row))


if __name__ == "__main__":
    solve()
