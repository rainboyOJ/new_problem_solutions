#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 00:04
# update_at: 2026-10-09 00:14

import re
import sys

SPACE_RUN = re.compile(rb' +')  # 只压 ASCII 空格；Tab、\v、\f 不算空格，与 main.cpp 判据一致


def solve() -> None:
    """整行读入句子，把每段连续空格压成一个空格后输出；无输入时不输出任何内容。"""
    line = sys.stdin.buffer.readline()
    if not line:
        return                       # 与 C++ 侧 getline 失败时同样不输出任何内容
    line = line.removesuffix(b'\n')  # 行尾 LF
    line = line.removesuffix(b'\r')  # CRLF 数据在行尾残留的 '\r'（只去一个，与 C++ 对齐）
    sys.stdout.buffer.write(SPACE_RUN.sub(b' ', line) + b'\n')


if __name__ == "__main__":
    solve()
