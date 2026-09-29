#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 18:01
# update_at: 2026-09-29 18:01

import sys


def solve() -> None:
    n = int(sys.stdin.buffer.read())  # 小朋友人数
    # 每人苹果数互不相同且至少 1 个，最省的取法就是 1, 2, ..., n
    total = n * (n + 1) // 2  # 等差数列求和，n(n+1) 必为偶数，整除不会有误差
    print(total)


if __name__ == "__main__":
    solve()
