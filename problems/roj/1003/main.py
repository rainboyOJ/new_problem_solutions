#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 12:19
# update_at: 2026-09-29 12:19

import sys

WIDTH = 8  # 题面格式：每个整数占 8 个字符宽度，右对齐


def solve() -> None:
    """读入一行三个整数，各自按宽度 WIDTH 右对齐成字段，用一个空格连成一行输出。"""
    a, b, c = map(int, sys.stdin.buffer.read().split())  # 解包成三个名字，个数不符立刻报错
    # `:>WIDTH` 左侧补空格到最小宽度、超过 WIDTH 个字符不截断；
    # print 默认 sep=' '，正是题面要求的字段间那一个空格
    print(*(f"{number:>{WIDTH}}" for number in (a, b, c)))


if __name__ == "__main__":
    solve()
