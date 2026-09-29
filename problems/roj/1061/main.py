#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-06 10:30
# update_at: 2026-07-06 10:30

import sys


def solve() -> None:
    data = map(int, sys.stdin.buffer.read().split())
    n = next(data)
    total = sum(data)
    avg = total / n
    print(f"{total} {avg:.5f}")


if __name__ == "__main__":
    solve()
