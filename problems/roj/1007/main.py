#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 12:44
# update_at: 2026-09-29 12:44

import sys


def solve() -> None:
    """读入一行里的三个整数，输出表达式 (a+b)×c 的值。"""
    a, b, c = map(int, sys.stdin.buffer.read().split())
    print((a + b) * c)


if __name__ == "__main__":
    solve()
