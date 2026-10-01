#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 10:13
# update_at: 2026-10-01 10:23

import sys


def ring_cost(counts: list[int], total: int) -> int | None:
    """环形数组的最少相邻交换次数；total 不能被长度整除时返回 None。

    设净流量 f_i 为从位置 i 搬到位置 i+1（下标按环取模）的摊点数，守恒式
    f_i = f_{i-1} + a_i - avg 给出 f_i = K + b_i，其中 b_i = 前 i 项之和 - i*avg
    只由 counts 决定。总交换次数是 sum|f_i|，对 K 取中位数即得最小值；
    counts 原地复用成 b 数组，省掉一次 O(n) 的额外分配。
    """
    n = len(counts)
    if total % n:
        return None
    avg = total // n
    prefix = 0
    for i, a in enumerate(counts, 1):
        prefix += a
        counts[i - 1] = prefix - i * avg
    counts.sort()
    pivot = counts[n // 2]                      # 中位数：偶数长度取哪个中位点代价都一样
    return sum(abs(b - pivot) for b in counts)  # 等价于 sum|b_i - median|


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m, t = next(data), next(data), next(data)

    row = [0] * n   # row[r] = 第 r 行感兴趣的摊点数
    col = [0] * m
    for _ in range(t):
        row[next(data) - 1] += 1
        col[next(data) - 1] += 1

    # 横向交换只改变列计数、纵向交换只改变行计数，两件事互不干涉，代价可以直接相加；
    # 各自可行当且仅当总数能被行数/列数整除。
    row_cost = ring_cost(row, t)
    col_cost = ring_cost(col, t)

    if row_cost is None and col_cost is None:
        print("impossible")
    elif col_cost is None:
        print("row", row_cost)
    elif row_cost is None:
        print("column", col_cost)
    else:
        print("both", row_cost + col_cost)


if __name__ == "__main__":
    solve()
