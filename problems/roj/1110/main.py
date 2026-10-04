#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-01-09 10:00
# update_at: 2026-01-09 10:00

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    a = [next(data) for _ in range(n)]
    x = next(data)

    # next + enumerate 在找到第一个匹配值时立刻短路，下标保持从 1 开始。
    pos = next((i for i, v in enumerate(a, 1) if v == x), -1)
    print(pos)


if __name__ == "__main__":
    solve()
