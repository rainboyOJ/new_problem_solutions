#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 04:40
# update_at: 2026-10-02 04:40

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    k = next(data)  # 输入只有一个整数 K

    s = 0.0  # S_n = 1 + 1/2 + ... + 1/n，严格递增
    n = 0
    while s <= k:  # 边加边判：S_n 一旦超过 K 就停
        n += 1
        s += 1.0 / n

    print(n)


if __name__ == "__main__":
    solve()
