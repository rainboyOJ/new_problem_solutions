#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 22:56
# update_at: 2026-10-01 22:56

import sys


def best_energy(marks: list[int], n: int) -> int:
    """项链上 n 颗珠子全部聚合时能释放的最大总能量。"""
    a = marks * 2  # 环拆成链再复制一倍：任何区间 [i, i+n-1] 都是环上的一种起点
    size = 2 * n
    # f[i][j]：把 a[i..j] 这串连续珠子聚成一颗时释放的最大能量；长度为 1 时无需聚合，值为 0
    f = [[0] * size for _ in range(size)]

    for length in range(2, n + 1):      # 长度超过 n 的区间不是环上的连续段，不必计算
        for i in range(size - length):  # 右端留一个 a[j+1] 当聚合后珠子的尾标记
            j = i + length - 1
            head, tail = a[i], a[j + 1]  # [i,j] 全部聚合后得到珠子 (head, tail)
            row = f[i]
            for k in range(i, j):        # 最后一步：[i,k] 与 [k+1,j] 各自的珠子再聚合
                energy = row[k] + f[k + 1][j] + head * a[k + 1] * tail
                if energy > row[j]:
                    row[j] = energy

    # 环上每种起点都对应一个长度为 n 的区间，取最大者
    return max(f[i][i + n - 1] for i in range(n))


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    marks = [next(data) for _ in range(n)]  # 只顺序取 N 个标记：多余 token 不再消费
    print(best_energy(marks, n))


if __name__ == "__main__":
    solve()
