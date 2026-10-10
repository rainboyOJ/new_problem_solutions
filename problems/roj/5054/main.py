#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 00:41
# update_at: 2026-10-09 00:41

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    a = next(data, None)  # 题面只给一个整数；None 表示空输入
    # 开区间 (1, 100)：两端都不取；不满足时保持 0 字节输出（连换行也不打印）
    if a is not None and 1 < a < 100:
        print("yes")


if __name__ == "__main__":
    solve()
