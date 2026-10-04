#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 12:32
# update_at: 2026-09-29 12:32

import sys

HEIGHT = 3  # 三角形行数
HALF_BASE = 2  # 首行左侧空格数，也就是 (底边宽度 5 - 1) // 2


def solve() -> None:
    """读入一个字符，输出底边 5 个字符、高 3 行的等腰三角形（行尾不留空格）。"""
    ch = sys.stdin.read().strip()
    print('\n'.join(' ' * (HALF_BASE - row) + ch * (2 * row + 1) for row in range(HEIGHT)))


if __name__ == "__main__":
    solve()
