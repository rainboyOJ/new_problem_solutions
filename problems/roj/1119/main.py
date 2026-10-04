#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    rows = [[next(data) for _ in range(5)] for _ in range(5)]
    m, n = next(data) - 1, next(data) - 1
    rows[m], rows[n] = rows[n], rows[m]
    print('\n'.join(' '.join(map(str, r)) for r in rows))


if __name__ == "__main__":
    solve()
