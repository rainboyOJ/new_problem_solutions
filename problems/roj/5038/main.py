#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 22:46
# update_at: 2026-10-08 22:46

import sys
from math import isqrt


def solve() -> None:
    """第 k 扇门被翻转的次数等于 k 的正约数个数，为奇数当且仅当 k 是完全平方数。"""
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)  # 题面保证 2 <= n <= 1000

    # 直接输出 1^2, 2^2, ..., 直到不超过 n —— 即所有开着的门号
    print(' '.join(str(i * i) for i in range(1, isqrt(n) + 1)))


if __name__ == "__main__":
    solve()
