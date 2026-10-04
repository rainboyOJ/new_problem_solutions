#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2025-07-11 17:15
# update_at: 2026-10-04 09:30

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    x, y = next(data), next(data)
    inside = -1 <= x <= 1 and -1 <= y <= 1
    print("yes" if inside else "no")


if __name__ == "__main__":
    solve()
