#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 19:03
# update_at: 2026-09-29 19:07

import sys


def solve() -> None:
    """把第二行读到的数组倒着输出，元素之间用空格分隔。"""
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)  # 题面的元素个数，与后面 token 数一致，仅作读入说明
    values = [next(data) for _ in range(n)]
    print(*reversed(values))  # print 的 sep=' ' 正好对上题面要求的空格分隔


if __name__ == "__main__":
    solve()
