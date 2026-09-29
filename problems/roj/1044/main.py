#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 16:32
# update_at: 2026-09-29 16:32

import sys


def solve() -> None:
    """读入一个正整数 n，输出 n 是否为两位数（10 到 99）的判断结果。"""
    n = int(sys.stdin.buffer.read())  # 输入只有一个整数，带换行的字节串 int 也能直接解析
    print(int(10 <= n <= 99))         # 链式比较给出 bool，转成题面要求的 0/1


if __name__ == "__main__":
    solve()
