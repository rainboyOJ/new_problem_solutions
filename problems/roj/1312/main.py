#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 04:35
# update_at: 2026-09-30 04:35

import sys


def solve() -> None:
    x, y, z = map(int, sys.stdin.buffer.read().split())

    # a[i]：第 i 个月的成虫对数；b[i]：第 i 个月产下的卵对数。下标即月份，0 号位当哨兵 0。
    a = [0] * (z + 3)
    b = [0] * (z + 3)

    for i in range(1, x + 1):
        a[i] = 1  # 成虫不死：前 x 个月始终只有最初那对，尚未到产卵时间

    for i in range(x + 1, z + 2):
        b[i] = a[i - x] * y  # 第 i-x 月已有的每对成虫，过 x 个月在本月产 y 对卵
        a[i] = a[i - 1] + b[i - 2]  # 成虫不死 + 卵过两个月孵化：上月成虫 + 两月前的卵

    print(a[z + 1])  # 从第 1 个月再过 Z 个月，即第 Z+1 个月


if __name__ == "__main__":
    solve()
