#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 15:03
# update_at: 2026-10-07 15:03

import sys
from collections.abc import Iterator
from math import sumprod

type Matrix = list[list[int]]  # 矩阵按行存：matrix[i] 是第 i 行，元素是整数
type Tokens = Iterator[bytes]  # 一次读入后按空白切分的整数流，顺序消费


def read_matrix(rows: int, cols: int, data: Tokens) -> Matrix:
    """从整数流里顺序取数，读入 rows 行 cols 列的矩阵。"""
    return [[int(next(data)) for _ in range(cols)] for _ in range(rows)]


def multiply(a: Matrix, b: Matrix) -> Matrix:
    """按定义做矩阵乘法：C[i][j] = Σ_t A[i][t] * B[t][j]。"""
    columns = list(zip(*b))  # zip(*b) 把 B 的第 j 列收成一个元组
    return [[sumprod(row, col) for col in columns] for row in a]  # sumprod 就是点积


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n, m, k = int(next(data)), int(next(data)), int(next(data))
    a = read_matrix(n, m, data)
    b = read_matrix(m, k, data)
    for row in multiply(a, b):
        print(' '.join(map(str, row)))


if __name__ == "__main__":
    solve()
