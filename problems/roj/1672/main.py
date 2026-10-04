#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-10-04 10:22

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    # 第一行包含两个整数 m 和 n，表示矩阵的行数与列数
    m, n = next(data), next(data)
    heights = [next(data) for _ in range(m * n)]
    # 玉米杆高度差 = 最大高度 - 最小高度
    diff = max(heights) - min(heights)
    print(diff)


if __name__ == "__main__":
    solve()
