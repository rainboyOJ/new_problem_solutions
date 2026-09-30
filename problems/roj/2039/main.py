#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 04:30
# update_at: 2026-10-01 04:30

import sys


def long_division_digits(n: int, d: int) -> str:
    """模拟 n/d 的长除法：返回整数部分、纯小数部分和循环节起点。

    余数每出现一次就登记它的位数；同一个余数第二次出现的位置
    就是循环节的起点，这保证总步数不超过 d（余数只有 d 种取值）。
    """
    seen: dict[int, int] = {}  # 余数 -> 它出现时已在小数部分写下的位数
    digits: list[str] = []     # 小数点后的数字串
    r = n % d                  # 当前余数，0 表示已经除尽
    while r and r not in seen:
        seen[r] = len(digits)
        r *= 10
        digits.append(str(r // d))
        r %= d

    body = ''.join(digits[: seen[r]]) + '(' + ''.join(digits[seen[r]:]) + ')' if r else ''.join(digits)
    return f'{n // d}.{body or "0"}'


def solve() -> None:
    n, d = map(int, sys.stdin.buffer.read().split())
    text = long_division_digits(n, d)
    print('\n'.join(text[i:i + 76] for i in range(0, len(text), 76)))


if __name__ == "__main__":
    solve()
