#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 19:49
# update_at: 2026-09-29 19:50

import sys


def solve() -> None:
    tokens = list(map(int, sys.stdin.buffer.read().split()))
    m, n = tokens[0], tokens[1]                 # 行数、列数
    total = m * n                               # 总像素数

    a = tokens[2:2 + total]                     # 第一幅图像
    b = tokens[2 + total:2 + 2 * total]         # 第二幅图像

    same = sum(x == y for x, y in zip(a, b))    # 对应位置颜色相同个数
    print(f"{same / total * 100:.2f}")


if __name__ == "__main__":
    solve()
