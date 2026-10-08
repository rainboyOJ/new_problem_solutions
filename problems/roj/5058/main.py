#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 01:10
# update_at: 2026-10-09 01:10

import sys


def solve() -> None:
    """读入三个实数，输出其中最大的数（%g 去掉冗余尾零，整数答案不打 ".00"）。"""
    a, b, c = map(float, sys.stdin.buffer.read().split())
    print('%g' % max(a, b, c))  # 与 C++ 的 cout 默认格式/printf("%g") 逐字节一致


if __name__ == "__main__":
    solve()
