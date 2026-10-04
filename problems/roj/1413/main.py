#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 09:24
# update_at: 2026-09-30 09:24

import sys

B_MAX = 40  # 进制 B 的枚举上界（含）


def to_base(s: str, base: int) -> int:
    """把数字串 s 当作 base 进制转成十进制；出现非法数字则返回 -1。"""
    value = 0
    for ch in s:
        digit = ord(ch) - ord('0')
        if digit >= base:  # 某一位数字超出进制允许范围，非法
            return -1
        value = value * base + digit
    return value


def solve() -> None:
    p, q, r = sys.stdin.read().split()

    # 从小到大枚举进制，第一个满足 p*q=r 的就是答案
    ans = next(
        (
            base
            for base in range(2, B_MAX + 1)
            if (x := to_base(p, base)) > 0
            and x * to_base(q, base) == to_base(r, base)
        ),
        0,  # 没有任何进制合法
    )
    print(ans)


if __name__ == "__main__":
    solve()
