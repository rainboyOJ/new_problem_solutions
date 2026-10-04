#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 22:02
# update_at: 2026-09-29 22:02

import sys


def solve() -> None:
    # 题面说"没有多余的前导 0"，但 int() 对 "0" 或偶发前导 0 都能正确解析，
    # 这里无需任何清洗；读入即两个十进制大整数字符串。
    a, b = (int(line) for line in sys.stdin.read().split())
    print(a * b)  # str(int) 天然无前导 0，含 0 * x = 0 的情形


if __name__ == "__main__":
    solve()
