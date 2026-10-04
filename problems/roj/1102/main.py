#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 18:53
# update_at: 2026-09-29 18:53

import sys


def solve() -> None:
    """统计整数序列中与指定数字相同的数的个数。"""
    data = list(map(int, sys.stdin.buffer.read().split()))
    n, *rest = data
    seq = rest[:n]
    m = rest[n] if len(rest) > n else 0  # 兼容空序列
    print(seq.count(m))


if __name__ == "__main__":
    solve()
