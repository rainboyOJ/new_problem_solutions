#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 00:36
# update_at: 2026-10-09 00:39

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    a = next(data, None)                       # 输入只有一个正整数 a
    if a is None:
        return

    if a % 2 == 0:
        print("yes")                           # 奇数分支刻意不输出：连空行都不能有


if __name__ == "__main__":
    solve()
