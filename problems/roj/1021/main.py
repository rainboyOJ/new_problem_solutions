#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 13:42
# update_at: 2026-09-29 13:42

import sys


def solve() -> None:
    code = int(sys.stdin.buffer.read())  # 一个整数：可见字符的 ASCII 码
    print(chr(code))                     # chr 把码点变回字符，一次映射完成


if __name__ == "__main__":
    solve()
