#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 01:46
# update_at: 2026-10-09 01:46

import sys


def solve() -> None:
    """要买尽量多的笔，就先按最便宜的 4 元笔算出笔数上界 k = x // 4，
    再看余数 r；把若干支 4 元笔换成更贵的笔补上差价，笔数不变。
    同笔数时数据采用「6 元笔尽量多」（即 (a, b, c) 字典序最大），
    故 r = 2 用 1 支 6 元笔而非 2 支 5 元笔。"""
    data = iter(map(int, sys.stdin.buffer.read().split()))
    x = next(data, None)  # 数据保证 x >= 4 且可恰好花光；空输入直接返回
    if x is None:
        return

    k, r = divmod(x, 4)  # k = 笔数上界，r = 余数
    a, b, c = 0, 0, k    # 6 元、5 元、4 元笔数，先全部按 4 元笔算再按余数替换
    if r == 1:           # 1 支 4 元 -> 1 支 5 元
        b, c = 1, c - 1
    elif r == 2:         # 1 支 4 元 -> 1 支 6 元
        a, c = 1, c - 1
    elif r == 3:         # 2 支 4 元 -> 1 支 6 元 + 1 支 5 元
        a, b, c = 1, 1, c - 2

    print(a, b, c)


if __name__ == "__main__":
    solve()
