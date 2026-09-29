#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 16:21
# update_at: 2026-09-29 16:21

import sys


def solve() -> None:
    a, b, c = map(int, sys.stdin.buffer.read().split())  # 一行三个整数（可能为负）
    print(max(a, b, c))  # 内建 max：三者最大值


if __name__ == "__main__":
    solve()
