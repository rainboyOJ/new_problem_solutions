#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 22:37
# update_at: 2026-10-08 22:37

import sys


def solve() -> None:
    """输出 n 行直角三角形：第 i 行恰好 i 个 '*'，行末一个换行（n=0 时输出空）。"""
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    n = int(data[0])
    for row in range(1, n + 1):
        print("*" * row)


if __name__ == "__main__":
    solve()
