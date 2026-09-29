#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 14:43
# update_at: 2026-09-29 14:43

import sys


def solve() -> None:
    n = int(sys.stdin.readline())        # 按整数读入，三段数位各自成项、逐项拼接
    sign = -1 if n < 0 else 1            # C 的 / 与 % 向零截断，Python 的 // % 要手动补符号
    m = abs(n)
    ones = sign * (m % 10)               # 个位：反向后的第 1 位
    tens = sign * (m // 10 % 10)         # 十位：反向后的第 2 位
    rest = sign * (m // 100)             # 更高位：作为整体原样接在末尾
    print(f"{ones}{tens}{rest}")         # 逐段打印，前导零自然保留（100 → 001）


if __name__ == "__main__":
    solve()
