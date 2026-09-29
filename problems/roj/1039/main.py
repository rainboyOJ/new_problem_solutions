#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 15:40
# update_at: 2026-09-29 15:40

import sys

SIGN_NAME = {1: "positive", 0: "zero", -1: "negative"}  # 符号值 → 题面要求的单词


def sign(n: int) -> int:
    """n 的符号值：正数 1、零 0、负数 -1。"""
    return (n > 0) - (n < 0)


def solve() -> None:
    (n,) = map(int, sys.stdin.buffer.read().split())
    print(SIGN_NAME[sign(n)])


if __name__ == "__main__":
    solve()
