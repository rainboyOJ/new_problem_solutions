#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 22:08
# update_at: 2026-10-08 22:08

import sys


def solve() -> None:
    """读入 n，输出 1×2×…×n；Python 整数无限精度，不存在 20! 溢出问题。"""
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    ans = 1
    for i in range(1, n + 1):
        ans *= i

    print(ans)


if __name__ == "__main__":
    solve()
