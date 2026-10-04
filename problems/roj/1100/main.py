#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 18:52
# update_at: 2026-09-29 18:52

import sys
from math import isqrt


def full_blocks(days: int) -> int:
    """完整发放块的编号 n：第 k 块恰好占 k 天，1..n 块共 n(n+1)/2 天不超过 days。"""
    return (isqrt(8 * days + 1) - 1) // 2  # 解 n^2+n-2*days <= 0，取最大整数根


def gold_coins(days: int) -> int:
    """前 days 天的金币总数：完整块用平方和公式，尾块按 n+1 枚金币补齐。"""
    n = full_blocks(days)
    tail_days = days - n * (n + 1) // 2  # 最后一个不完整块占用的天数
    return n * (n + 1) * (2 * n + 1) // 6 + tail_days * (n + 1)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    days = next(data)
    print(gold_coins(days))


if __name__ == "__main__":
    solve()
