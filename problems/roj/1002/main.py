#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 11:17
# update_at: 2026-09-29 11:17

import sys


def solve() -> None:
    """读入一行三个整数，输出第二个。"""
    # `_` 收下第一个、`*_` 吃掉第三个，只有中间的值留下；解包失败即说明输入不是三个整数
    _, second, *_ = map(int, sys.stdin.buffer.read().split())
    print(second)


if __name__ == "__main__":
    solve()
