#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 18:04
# update_at: 2026-09-29 18:04

import sys


def solve() -> None:
    k = int(sys.stdin.buffer.read())
    total = 0.0          # 累计的调和级数 S_n
    n = 0
    while total <= k:    # 逐项累加，首次超过 k 的 n 即答案
        n += 1
        total += 1 / n
    print(n)


if __name__ == "__main__":
    solve()
