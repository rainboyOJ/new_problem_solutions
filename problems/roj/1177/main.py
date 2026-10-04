#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 22:00
# update_at: 2026-07-05 22:00

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    odds = sorted(v for _, v in zip(range(n), data) if v & 1)  # 只保留奇数并升序排序
    print(','.join(map(str, odds)))


if __name__ == "__main__":
    solve()
