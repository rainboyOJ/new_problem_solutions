#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 15:24
# update_at: 2026-09-29 15:24

import sys


def solve() -> None:
    """读入一行里的两个正整数，输出它们的乘积。"""
    a, b = map(int, sys.stdin.buffer.read().split())
    print(a * b)


if __name__ == "__main__":
    solve()
