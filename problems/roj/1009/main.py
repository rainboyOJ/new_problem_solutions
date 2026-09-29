#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 13:07
# update_at: 2026-09-29 13:07

import sys


def solve() -> None:
    dividend, divisor = map(int, sys.stdin.buffer.read().split())

    # 评测数据按 C 语义给答案：商向零截断，再用商回推余数。
    # Python 的 // 是向下取整，除数为负时会整体偏移，必须自己截断。
    opposite_sign = (dividend < 0) != (divisor < 0)   # 异号 → 商为负
    quot = abs(dividend) // abs(divisor)              # 先算非负商
    if opposite_sign:
        quot = -quot
    rem = dividend - quot * divisor                   # 余数与截断商配套，符号随被除数

    print(quot, rem)


if __name__ == "__main__":
    solve()
