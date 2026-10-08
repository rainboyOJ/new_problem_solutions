#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 16:13
# update_at: 2026-10-08 16:13

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    evens = range(2, n + 1, 2)  # 1~n 内的偶数；n = 1 时为空，此时答案为空串
    if evens:
        print(" ".join(map(str, evens)))


if __name__ == "__main__":
    solve()
