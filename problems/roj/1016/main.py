#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 13:32
# update_at: 2026-09-29 13:32

import struct

# 题面问的是 C/C++ 里 int / short 各占多少字节，而 Python 的 int 是任意精度对象，
# 拿 sizeof 去量 Python 对象没有意义。struct 用的正是 C 的 ABI 格式字符：
# 'i' 对应 int、'h' 对应 short，calcsize 返回该类型在当前平台的字节数，
# 与 C++ 的 sizeof(int) / sizeof(short) 同义。
INT_SIZE = struct.calcsize("i")    # int：常见 32 位平台为 4 字节
SHORT_SIZE = struct.calcsize("h")  # short：C 标准只要求不超过 int，常见为 2 字节


def solve() -> None:
    # 本题无输入：两个量各只出现一次，按题面顺序交给 print 的空格分隔输出。
    print(INT_SIZE, SHORT_SIZE)


if __name__ == "__main__":
    solve()
