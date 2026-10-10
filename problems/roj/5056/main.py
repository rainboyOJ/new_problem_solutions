#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 00:36
# update_at: 2026-10-09 00:38

import sys


def solve() -> None:
    """读入温度 t，闭区间 [25, 30] 内输出 ok!，否则输出 no!（t 为整数）。"""
    data = iter(sys.stdin.buffer.read().split())
    t = int(next(data))
    print("ok!" if 25 <= t <= 30 else "no!")


if __name__ == "__main__":
    solve()
