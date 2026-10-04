#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 18:40
# update_at: 2026-09-29 18:40

import sys
from functools import cache

TARGET = "2"  # 题目要统计的目标数字；用字符串形式是为了配合 str.count


@cache
def count_upto(x: int) -> int:
    """统计 1..x 中数字 2 出现的总次数；区间答案用 count_upto(right) - count_upto(left - 1)。"""
    if x < 2:
        return 0
    quotient, remainder = divmod(x, 10)
    if quotient == 0:
        return 1  # 个位数：只有 2 本身算一个

    # 把 0..x 按"高位 + 个位"拆开，逐块统计（x = 10 * quotient + remainder）
    blocks = 10 * count_upto(quotient - 1)  # 高位取 0..quotient-1 时，高位里的 2 被 10 个低位各复制一遍
    tail_low = quotient                     # 这些完整块里，个位每个数字都恰好出现 quotient 次
    tail_high = (remainder + 1) * str(quotient).count(TARGET)  # 高位固定在 quotient，低位有 remainder+1 种
    ones_place = remainder >= 2             # 个位从 0 走到 remainder，只有 2 落在这段里

    return blocks + tail_low + tail_high + ones_place


def solve() -> None:
    left, right = map(int, sys.stdin.buffer.read().split())
    print(count_upto(right) - count_upto(left - 1))


if __name__ == "__main__":
    solve()
