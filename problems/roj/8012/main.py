#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 19:46
# update_at: 2026-10-08 19:46

import sys


def solve() -> None:
    """读入 m, n，输出第 m 格到第 n 格的米粒总数（两格编号可能前后颠倒）。"""
    data = iter(map(int, sys.stdin.buffer.read().split()))
    m, n = next(data), next(data)

    low, high = min(m, n), max(m, n)  # 题面没保证 m <= n，真实数据 gwdml4 就是 30 25
    total = (1 << high) - (1 << (low - 1))  # 区间和公式：2^high - 2^(low-1)
    print(total)


if __name__ == "__main__":
    solve()
