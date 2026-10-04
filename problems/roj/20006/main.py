#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 19:29
# update_at: 2026-10-02 19:29

import sys
from itertools import cycle

QUOTES = ("``", "''")  # 第 1、3、5… 个双引号用左引号，第 2、4、6… 个用右引号


def solve() -> None:
    """把文章中交替出现的双引号改写成 TeX 的左、右双引号。"""
    text = sys.stdin.buffer.read().decode()
    head, *parts = text.split('"')  # n 个双引号把文章切成 n+1 段
    # 第 i 个双引号位于第 i 段与第 i+1 段之间；cycle 让引号奇偶交替
    sys.stdout.write(head + ''.join(q + part for q, part in zip(cycle(QUOTES), parts)))


if __name__ == "__main__":
    solve()
