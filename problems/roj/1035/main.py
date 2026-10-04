#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 16:01
# update_at: 2026-09-29 16:01

import sys


def nth_term(a1: int, a2: int, n: int) -> int:
    """等差数列第 n 项：公差 d = a2 - a1，第 n 项 = a1 + (n-1)·d。"""
    d = a2 - a1  # 公差：每一项相对前一项的固定增量
    return a1 + (n - 1) * d


def solve() -> None:
    a1, a2, n = map(int, sys.stdin.read().split())
    print(nth_term(a1, a2, n))


if __name__ == "__main__":
    solve()
