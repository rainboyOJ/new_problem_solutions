#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 15:37
# update_at: 2026-09-29 15:37

import sys


def solve() -> None:
    """读入一个浮点数，输出它保留两位小数的绝对值。"""
    data = iter(map(float, sys.stdin.buffer.read().split()))
    value = next(data)  # 输入只有一个实数，按位置顺序消费
    # 先取绝对值再格式化：负的极小数（如 -0.001）直接格式化会打印出 "-0.00"
    print(f"{abs(value):.2f}")


if __name__ == "__main__":
    solve()
