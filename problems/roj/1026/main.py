#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 14:04
# update_at: 2026-09-29 14:04

import struct
import sys


def to_float32(text: str) -> float:
    """按 C++ float 的精度读入：先解析成 double，再截回单精度的精确值。"""
    return struct.unpack("f", struct.pack("f", float(text)))[0]


def solve() -> None:
    ch, a, b, c = sys.stdin.read().split()  # cin >> 按空白分词，四行还是一行都一样
    # int() 抹掉整数可能的前导 0；两个浮点都要保留 6 位小数
    print(ch, int(a), f"{to_float32(b):.6f}", f"{float(c):.6f}")


if __name__ == "__main__":
    solve()
