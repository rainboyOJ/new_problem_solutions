#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 10:13
# update_at: 2026-10-01 10:17

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    coords: list[int] = sorted(next(data) for _ in range(n))  # 题面第二行的 N 个商店坐标

    # 排序后把最小与最大配成一组：|x-B_i|+|x-B_{N+1-i}| >= B_{N+1-i}-B_i（三角不等式）。
    # 取 x 为中位数时它同时落在每一组的区间内，所有组同时取等，于是差的和就是最小值；
    # N 为奇数时正中间那个元素与自身配对，差恒为 0，不必特判。
    pairs: int = n // 2  # 能配成 (小, 大) 的组数

    print(sum(coords[n - 1 - i] - coords[i] for i in range(pairs)))


if __name__ == "__main__":
    solve()
