#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 02:00
# update_at: 2026-10-09 02:00

import sys


def solve() -> None:
    """读入一行里的三个整数，输出它们的和。"""
    data = iter(map(int, sys.stdin.buffer.read().split()))
    a, b, c = next(data, None), next(data, None), next(data, None)
    if a is None or b is None or c is None:
        return  # 防御非法输入：题面保证恰好读入三个整数

    print(a + b + c)  # Python 整数任意精度，10^6 级别的加法不存在溢出问题


if __name__ == "__main__":
    solve()
