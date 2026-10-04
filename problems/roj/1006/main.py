#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 12:44
# update_at: 2026-09-29 12:44

import sys


def solve() -> None:
    """读入一个非 0 的数，输出它的负数形式：已是负数保持原样，否则补一个负号。"""
    num_str = sys.stdin.read().strip()  # 整个输入只有一个 token，去掉首尾空白
    already_negative = num_str.startswith('-')
    print(num_str if already_negative else '-' + num_str)


if __name__ == "__main__":
    solve()
