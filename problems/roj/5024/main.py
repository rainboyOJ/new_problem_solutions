#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 22:23
# update_at: 2026-10-08 22:23

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    m = next(data)  # 目标值：求最小的 n 使 1 + 1/2 + ... + 1/n >= m

    # 与 C++ 解同阶：逐项累加直到部分和 >= m，按分母顺序加是数值上最稳的次序。
    # 必须写 1.0 / n，1 / n 会得到 0。
    sum_h = 0.0
    n = 0
    while sum_h < m:
        n += 1
        sum_h += 1.0 / n

    print(n)


if __name__ == "__main__":
    solve()
