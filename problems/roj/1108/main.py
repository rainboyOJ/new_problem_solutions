#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 19:14
# update_at: 2026-09-29 19:17

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)                                  # 向量维数，也是逐位对齐的位数
    a = [next(data) for _ in range(n)]              # 第一行向量 a 的 n 个分量
    b = [next(data) for _ in range(n)]              # 第二行向量 b 的 n 个分量
    print(sum(ai * bi for ai, bi in zip(a, b)))     # zip 逐位配对，sum 边乘边加


if __name__ == "__main__":
    solve()
