#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 01:33
# update_at: 2026-09-30 01:33

import sys


def solve() -> None:
    """读入 n 个整数，去重后升序输出。"""
    tokens = sys.stdin.buffer.read().split()
    n = int(tokens[0])                  # 题面的 n：只用来界定数据长度，去重后的个数由数据本身决定
    values = map(int, tokens[1 : n + 1])  # 题面保证的 n 个整数
    answer = sorted(set(values))        # set 去重、sorted 升序，两个要求一次给全
    print(" ".join(map(str, answer)))


if __name__ == "__main__":
    solve()
