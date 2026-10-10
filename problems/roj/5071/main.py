#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 02:20
# update_at: 2026-10-09 07:31

import sys


def solve() -> None:
    """百位与个位对调后按整数输出：个位为 0 时新数最高位变成 0，按整数输出即自然去掉前导零。"""
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    h = n // 100      # 百位
    t = n // 10 % 10  # 十位
    u = n % 10        # 个位
    print(u * 100 + t * 10 + h)


if __name__ == "__main__":
    solve()
