#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 01:33
# update_at: 2026-10-04 10:12

import sys


def solve() -> None:
    """读入 n 个整数，去重后升序输出。"""
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)                      # 题面的 n：只用来界定数据长度，去重后的个数由数据本身决定
    answer = sorted({next(data) for _ in range(n)})  # set 去重、sorted 升序，两个要求一次给全
    print(" ".join(map(str, answer)))


if __name__ == "__main__":
    solve()
