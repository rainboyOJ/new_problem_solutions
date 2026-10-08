#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 02:20
# update_at: 2026-10-09 07:23

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    # 5 个小朋友的初始糖果数，按 1..5 号顺序读入；缺输入时该项为 None，直接结束不猜值
    a = next(data, None)
    b = next(data, None)
    c = next(data, None)
    d = next(data, None)
    e = next(data, None)
    if None in (a, b, c, d, e):
        return

    # 严格按 1 -> 5 号的顺序模拟：轮到的人用的已是前面分给他的最新数量。
    # share = floor(c / 3) 是一份的量，余数 c % 3 被当场吃掉，不再出现。
    share = a // 3  # 1 号：留一份，另两份给 2 号、5 号
    a, b, e = share, b + share, e + share

    share = b // 3  # 2 号：留一份，另两份给 1 号、3 号
    b, a, c = share, a + share, c + share

    share = c // 3  # 3 号：留一份，另两份给 2 号、4 号
    c, b, d = share, b + share, d + share

    share = d // 3  # 4 号：留一份，另两份给 3 号、5 号
    d, c, e = share, c + share, e + share

    share = e // 3  # 5 号：留一份，另两份给 4 号、1 号
    e, d, a = share, d + share, a + share

    # 题面「按 5 位宽度输出」：每个数占 5 位右对齐，相邻数字之间无分隔符
    print(f"{a:5d}{b:5d}{c:5d}{d:5d}{e:5d}")


if __name__ == "__main__":
    solve()
