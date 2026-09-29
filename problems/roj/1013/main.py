#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 13:19
# update_at: 2026-09-29 13:19

import sys


def solve() -> None:
    fahrenheit = float(sys.stdin.readline())
    celsius = 5 * (fahrenheit - 32) / 9  # 题面公式 C = 5×(F-32)÷9
    print(f"{celsius:.5f}")


if __name__ == "__main__":
    solve()
