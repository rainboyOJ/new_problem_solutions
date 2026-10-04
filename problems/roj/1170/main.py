#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 21:52
# update_at: 2026-09-29 22:00

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)  # 唯一的输入量：指数 n
    print(2**n)  # Python 整数任意精度，n = 100 时 31 位十进制数一次算出


if __name__ == "__main__":
    solve()
