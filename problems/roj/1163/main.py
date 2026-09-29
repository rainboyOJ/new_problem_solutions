#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 22:14
# update_at: 2026-09-29 22:14

import sys


def ackermann(m: int, n: int) -> int:
    """阿克曼函数 A(m, n)：按层自底向上填表，消掉朴素递归的重复子问题。"""
    # rows[k][j] = A(k, j)；第 k 层只读第 k-1 层，所以可以逐层往后填
    rows: list[list[int]] = [[] for _ in range(m + 1)]

    def value(k: int, j: int) -> int:
        """取 A(k, j)：按需把第 k 层延长到下标 j，递归深度只有 k 层。"""
        if k == 0:
            return j + 1                                   # 唯一出口：A(0, j) = j + 1
        row = rows[k]
        while len(row) <= j:                               # 惰性填表：只算被问到的下标
            # A(k, 0) = A(k-1, 1)；A(k, t) = A(k-1, A(k, t-1))，左邻值就是上一层要取的列号
            column = row[-1] if row else 1
            row.append(value(k - 1, column))
        return row[j]

    return value(m, n)


def solve() -> None:
    m, n = map(int, sys.stdin.buffer.read().split())
    print(ackermann(m, n))


if __name__ == "__main__":
    solve()
