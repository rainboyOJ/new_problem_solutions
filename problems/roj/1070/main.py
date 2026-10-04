#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 17:27
# update_at: 2026-09-29 18:04

import sys

GROWTH = 1.001  # 每年增长 0.1%：当年人口乘以 1 + 0.001


def solve() -> None:
    base, years = map(int, sys.stdin.buffer.read().split())  # 人口基数 x、年数 n
    people = base * GROWTH**years  # 等比数列通项：n 年后人口 = x * 1.001**n
    print(f"{people:.4f}")


if __name__ == "__main__":
    solve()
