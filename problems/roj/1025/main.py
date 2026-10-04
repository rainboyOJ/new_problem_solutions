#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 13:54
# update_at: 2026-10-04 14:12

import sys


def solve() -> None:
    """读入一个双精度浮点数，按 %.12f 四舍五入保留 12 位小数输出。"""
    data = iter(map(float, sys.stdin.buffer.read().split()))
    x = next(data)          # IEEE-754 双精度，与 C++ 的 double 同一种类型
    print(f"{x:.12f}")      # 同时负责舍入与补零，尾随 0 不会被吃掉


if __name__ == "__main__":
    solve()
