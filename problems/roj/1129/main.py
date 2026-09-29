#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 20:16
# update_at: 2026-09-29 20:16

import sys

MAX_LEN = 255  # 题面保证字符串总长度不超过 255，超长部分按 std.cpp 的缓冲区规则不参与统计


def solve() -> None:
    line = sys.stdin.buffer.read().decode()  # 一整行输入：字母、数字、空格与标点混合

    # 只保留前 255 个字符，再数其中落在 '0'~'9' 的字符；str.isdigit() 会把上标等
    # 非 ASCII 数字也算进来，故显式比较区间。
    kept = line[:MAX_LEN]
    count = sum('0' <= ch <= '9' for ch in kept)
    print(count)


if __name__ == "__main__":
    solve()
