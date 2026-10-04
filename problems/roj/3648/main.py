#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 12:46
# update_at: 2026-10-02 12:46

import sys


def solve() -> None:
    a, b = map(int, sys.stdin.buffer.read().split())
    # 互素两币值不能凑出的最大值 = a*b - a - b（数论结论，证明见题解）
    print(a * b - a - b)


if __name__ == "__main__":
    solve()
