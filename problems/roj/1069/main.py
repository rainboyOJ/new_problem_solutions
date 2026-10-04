#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 17:09
# update_at: 2026-09-29 17:09

import sys


def solve() -> None:
    base, exponent = map(int, sys.stdin.buffer.read().split())

    # 题目保证 |a^n| <= 10^6，而 Python 的 ** 是精确的大整数快速幂，
    # 负底数、指数为 1 都天然正确，直接算即可。
    print(base ** exponent)


if __name__ == "__main__":
    solve()
