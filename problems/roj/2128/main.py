#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 07:50
# update_at: 2026-10-08 07:50

import sys

DIGITS_LIMIT = 500000  # 200000 位的乘数、400000 位的积，都要超过 CPython 默认的 4300


def solve() -> None:
    """读入两个大整数并输出乘积：十进制串 → int → 相乘，交给 CPython 的 C 层大整数乘法。"""
    # CPython 3.11+ 默认禁止超过 4300 位的十进制串与 int 互转，这里按数据上界放宽
    sys.set_int_max_str_digits(DIGITS_LIMIT)

    # 输入恰好两个数：直接解包，不用手算偏移，也不用 iter/next 的求值顺序陷阱
    a, b = map(int, sys.stdin.buffer.read().split())
    # 前导零、单独的 "0" 都由 int() 按数值语义吸收，结果直接输出十进制即可
    sys.stdout.write(str(a * b) + "\n")


if __name__ == "__main__":
    solve()
