#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 15:48
# update_at: 2026-09-29 15:48

import sys


def solve() -> None:
    """读入一个正整数，按奇偶性输出 odd 或 even。"""
    n = int(sys.stdin.buffer.read())    # int() 容忍首尾空白和换行，直接吞掉整行
    print("odd" if n & 1 else "even")   # 只看二进制最低位：1 为奇数，0 为偶数


if __name__ == "__main__":
    solve()
