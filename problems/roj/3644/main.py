#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 12:33
# update_at: 2026-10-02 12:33

import sys


def solve() -> None:
    """按 20% / 30% / 50% 的权重求总成绩（整数运算，不做浮点）。"""
    homework, quiz, final = map(int, sys.stdin.buffer.read().split())
    # 权重同乘 100：20%/30%/50% 变成 2/3/5，分母统一为 10，一次整除即得整数总评
    weighted = homework * 2 + quiz * 3 + final * 5
    print(weighted // 10)


if __name__ == "__main__":
    solve()
