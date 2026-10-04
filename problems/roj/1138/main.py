#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 20:27
# update_at: 2026-09-29 20:27

import sys


def solve() -> None:
    """读入一行字符串，把其中的小写字母转成大写后输出。"""
    data = iter(sys.stdin.buffer.read().splitlines())  # 按行保留空格/换行，再逐行消费
    line = next(data).decode()                         # 取唯一的一行输入
    print(line.upper())                                # str.upper 只作用于小写字母，数字、符号、大写字母不受影响


if __name__ == "__main__":
    solve()
