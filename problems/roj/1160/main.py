#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 21:25
# update_at: 2026-09-29 21:26

import sys


def solve() -> None:
    """读入唯一的非负整数，输出它的倒序数。"""
    n = int(sys.stdin.buffer.read())  # int() 自己会忽略行尾换行，不需要先 strip
    print(str(n)[::-1])               # 反转十进制数字串，末尾的 0 反转到最前面要原样输出


if __name__ == "__main__":
    solve()
