#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 15:47
# update_at: 2026-09-29 15:47

import sys

MARKS = '>=<'  # 下标 0/1/2 依次对应 x>y、x=y、x<y


def solve() -> None:
    x, y = map(int, sys.stdin.buffer.read().split())  # Python int 任意精度，32 位范围直接比
    is_less = x < y
    is_equal = x == y
    print(MARKS[2 * is_less + is_equal])  # x<y 记 2，相等记 1，否则记 0


if __name__ == "__main__":
    solve()
