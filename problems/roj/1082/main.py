#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 17:55
# update_at: 2026-09-29 17:55

import sys


def solve() -> None:
    a, b, n = map(int, sys.stdin.buffer.read().split())
    # 第 n 位小数 = floor(a·10ⁿ/b) 的个位：一次大整数除法直接取位，无需逐位模拟
    print(a * 10**n // b % 10)


if __name__ == "__main__":
    solve()
