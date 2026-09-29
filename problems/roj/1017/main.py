#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 13:30
# update_at: 2026-09-29 13:30

import struct

# 题目问 C/C++ 中 float、double 各占多少字节；
# Python 的 struct 模块用同样的 IEEE 754 单/双精度格式，calcsize 返回字节数。
FLOAT_SIZE = struct.calcsize("f")   # 单精度，4 字节
DOUBLE_SIZE = struct.calcsize("d")  # 双精度，8 字节


def solve() -> None:
    # 题目无输入，直接输出两个整数
    print(FLOAT_SIZE, DOUBLE_SIZE)


if __name__ == "__main__":
    solve()
