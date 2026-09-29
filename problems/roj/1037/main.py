#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 15:24
# update_at: 2026-09-29 15:24

import sys


def solve() -> None:
    n = int(sys.stdin.buffer.readline())  # 0 <= n < 31，单个整数
    print(1 << n)  # 左移 n 位即 2^n，整数精确无浮点误差


if __name__ == "__main__":
    solve()
