#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 04:18
# update_at: 2026-09-30 04:27

import sys


def solve() -> None:
    """读入两个高精度正整数，输出它们的积。"""
    # 两个操作数各占一行；split() 按空白切分，恰好得到两个 token
    m, n = sys.stdin.buffer.read().split()
    # int 是任意精度整数：竖式相乘和进位由解释器完成，100 位量级用 O(len(m)*len(n)) 的竖式
    print(int(m) * int(n))


if __name__ == "__main__":
    solve()
