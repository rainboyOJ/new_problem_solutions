#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 22:04
# update_at: 2026-09-29 22:04

import sys


def solve() -> None:
    n: int = int(sys.stdin.readline())
    print(n // 13)
    print(n % 13)


if __name__ == "__main__":
    solve()
