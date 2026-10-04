#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 16:57
# update_at: 2026-09-29 16:57

import sys


def solve() -> None:
    """读入 n 与 n 个非负整数，输出序列的最大跨度值（最大值减最小值）。"""
    data = sys.stdin.buffer.read().split()
    n = int(data[0])  # 题面的序列长度：只有紧随其后的 n 个数属于本序列

    # 一次扫描出最大值与最小值，两者的差就是跨度值；不排序、不建桶
    values = list(map(int, data[1:1 + n]))
    print(max(values) - min(values))


if __name__ == "__main__":
    solve()
