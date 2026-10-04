#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 17:53
# update_at: 2026-09-29 17:53

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    a, b = next(data), next(data)

    k = 1
    for _ in range(b):
        k = k * a % 1000  # 每次只保留末三位

    print(f"{k:03d}")


if __name__ == "__main__":
    solve()
