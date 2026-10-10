#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 22:57
# update_at: 2026-10-08 22:57

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    # 打擂台：依次消费每个数，严格大于当前最大值才更新位置，
    # 因此并列最大值保留第一次出现的位置。Python 整数无溢出问题，
    # 题面值域上界 2^32-1 直接可装。
    max_pos = 1
    max_val = next(data)
    for i in range(2, n + 1):
        value = next(data)
        if value > max_val:
            max_val = value
            max_pos = i

    print(max_pos)


if __name__ == "__main__":
    solve()
