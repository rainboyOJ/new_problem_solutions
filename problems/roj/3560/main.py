#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys


def check_digit(digits: str) -> str:
    """按 ISBN 规则算识别码：9 位依次乘 1..9 求和后 mod 11，余 10 记作 X。"""
    remainder = sum(int(d) * w for d, w in zip(digits, range(1, 10))) % 11
    return 'X' if remainder == 10 else str(remainder)


def solve() -> None:
    isbn = sys.stdin.readline().strip()
    body, given = isbn.rsplit('-', 1)        # 拆出前 9 位（含两个 -）与识别码
    digits = body.replace('-', '')           # 只剩 9 位数字
    correct = check_digit(digits)

    if given == correct:
        print('Right')
    else:
        print(f'{body}-{correct}')


if __name__ == "__main__":
    solve()
