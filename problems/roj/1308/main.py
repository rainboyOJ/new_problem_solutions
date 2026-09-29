#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 04:19
# update_at: 2026-09-30 04:37

import sys


def solve() -> None:
    """读入两个高精度正整数，输出它们的商和余数。"""
    # 两个操作数各占一行；split() 按空白切分，恰好得到两个 token
    a, b = map(int, sys.stdin.buffer.read().split())
    # int 是任意精度整数：竖式的逐位试商由解释器完成，同阶于手写长除法
    q, r = divmod(a, b)
    print(q, r, sep='\n')  # 商、余数各占一行


if __name__ == "__main__":
    solve()
