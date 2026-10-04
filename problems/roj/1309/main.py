#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 22:10
# update_at: 2026-07-05 22:10

import sys

DIGITS = '0123456789ABCDEF'   # 值 → N 进制字符，N 最大 16，恰好够用
VALUES = {c: i for i, c in enumerate(DIGITS)}          # 大写字母的值
VALUES |= {c.lower(): i for i, c in enumerate(DIGITS) if c.isalpha()}  # 补小写


def add_reverse(a: list[int], base: int) -> list[int]:
    """返回 a + reverse(a) 在 base 进制下的数码数组（低位在前，可能多一位）。"""
    s = [x + y for x, y in zip(a, a[::-1])]
    for i in range(len(s)):
        carry, s[i] = divmod(s[i], base)
        if carry:                                        # 进位累加到更高位
            if i + 1 < len(s):
                s[i + 1] += carry
            else:
                s.append(carry)
    return s


def solve() -> None:
    base_s, m = sys.stdin.read().split()
    base = int(base_s)                                  # 进制 N（2 < N <= 10 或 N = 16）
    a = [VALUES[c] for c in m][::-1]                    # 数码数组，低位在前

    for step in range(31):                              # 第 0 步先判初始是否回文
        is_palindrome = a == a[::-1]
        if is_palindrome:
            print(step)
            return
        if step == 30:                                  # 30 步用尽仍未回文
            break
        a = add_reverse(a, base)                        # 一次 N 进制加法

    print('Impossible')


if __name__ == "__main__":
    solve()
