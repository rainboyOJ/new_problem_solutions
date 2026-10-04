#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 02:40
# update_at: 2026-10-01 02:40

import sys
from collections.abc import Iterator

MAX_N = 300  # 题面要求枚举的范围 [1, 300]，与进制 B 无关
DIGITS = "0123456789ABCDEFGHIJ"  # 数码表：下标即权值，10~19 用 A~J 表示


def to_base(value: int, base: int) -> str:
    """把十进制正整数写成 base 进制串（最高位在前）。"""
    digits = ""
    while value:
        digits = DIGITS[value % base] + digits  # 余数从低位到高位产生，故前置拼接
        value //= base
    return digits


def palindrome_squares(base: int) -> Iterator[tuple[int, str]]:
    """产出 [1, MAX_N] 内所有「平方是回文数」的 (原数, 平方的 base 进制串)。"""
    for x in range(1, MAX_N + 1):
        square = to_base(x * x, base)
        if square == square[::-1]:  # 反转后相同即为回文
            yield x, square


def solve() -> None:
    base = int(sys.stdin.read())
    out = [f"{to_base(x, base)} {square}" for x, square in palindrome_squares(base)]
    print("\n".join(out))


if __name__ == "__main__":
    solve()
