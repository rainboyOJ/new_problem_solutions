#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 03:23
# update_at: 2026-10-02 03:23

import sys

DIGITS = "0123456789ABCDEFGHIJ"  # 数码 0..19；基数的绝对值不超过 20，超过 9 的用 A..J


def to_negative_base(value: int, base: int) -> str:
    """把十进制 value 写成基数 base（base < 0）下的数码串，高位在前。"""
    if value == 0:
        return "0"
    chars: list[str] = []
    while value:
        value, digit = divmod(value, base)  # Python 向下取整：digit 落在 (base, 0]
        if digit < 0:                       # 借一位，把负数码补成正数码 [0, |base|)
            digit -= base
            value += 1
        chars.append(DIGITS[digit])
    return "".join(reversed(chars))


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []

    for value, neg_base in zip(data, data):  # 同一行两个数：十进制数 N 与基数 -R
        digits = to_negative_base(value, neg_base)
        out.append(f"{value}={digits}(base{neg_base})")  # 基数按输入原样输出，故带负号

    print("\n".join(out))


if __name__ == "__main__":
    solve()
