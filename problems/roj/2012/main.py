#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 02:55
# update_at: 2026-10-01 02:56

import sys
from itertools import product


def is_cow_number(value: int, length: int, allowed: set[int]) -> bool:
    """value 的十进制写法恰好 length 位，且每一位数字都来自 allowed 集合。"""
    text = str(value)
    return len(text) == length and allowed.issuperset(map(int, text))


def build_numbers(digits: list[int], length: int) -> list[int]:
    """用给定数字（允许重复）拼出全部 length 位数；数字集不含 0，故首位必非 0。"""
    return [int(''.join(map(str, combo))) for combo in product(digits, repeat=length)]


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    count = int(data[0])                                # 第 1 行：数字的个数
    digits = [int(token) for token in data[1:1 + count]]
    allowed = set(digits)

    three_digit = build_numbers(digits, 3)              # 被乘数 a 的全部候选
    two_digit = build_numbers(digits, 2)                # 乘数 b 的全部候选

    # 竖式里由 a、b 算出的 3 个结果都要位数正确、数字合法：部分积各 3 位，最终积 4 位
    answer = sum(
        is_cow_number(a * b, 4, allowed)
        and is_cow_number(a * (b % 10), 3, allowed)      # b 的个位乘 a
        and is_cow_number(a * (b // 10), 3, allowed)     # b 的十位乘 a
        for a in three_digit
        for b in two_digit
    )
    print(answer)


if __name__ == "__main__":
    solve()
