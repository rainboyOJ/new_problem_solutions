#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 10:52
# update_at: 2026-10-01 10:52

import sys


def median_cost(values: list[int]) -> int:
    """把这些数平移到同一个点，最小的总距离 = 各点到中位数的绝对距离之和。"""
    values.sort()
    median = values[len(values) // 2]
    return sum(abs(v - median) for v in values)


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    n = data[0]
    xs = data[1::2][:n]  # 第 i 行读入的 x[i]
    ys = data[2::2][:n]  # 第 i 行读入的 y[i]

    # x 轴：目标是 n 个相邻格子 base, base+1, ..., base+n-1，排序后第 i 名士兵
    # 领第 i 个格子，因此把每人要走的偏移 i 提前扣掉，再对 base 取中位数。
    x_cost = median_cost([x - i for i, x in enumerate(sorted(xs))])
    # y 轴：全部站到同一行 Y，取 y 的中位数即可。
    print(x_cost + median_cost(ys))


if __name__ == "__main__":
    solve()
