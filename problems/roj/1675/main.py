#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-03-31 10:00
# update_at: 2026-03-31 10:00

import sys
from functools import cache


@cache
def count_partitions(remain: int, parts: int) -> int:
    """求将整数 remain 划分为 parts 份正整数的方案数。"""
    if remain < parts or parts <= 0:
        return 0
    if remain == parts or parts == 1:
        return 1
    # 状态转移：若划分包含 1，对应 count_partitions(remain - 1, parts - 1)；
    # 若每份均大于 1，每份各减 1，对应 count_partitions(remain - parts, parts)。
    return count_partitions(remain - 1, parts - 1) + count_partitions(remain - parts, parts)


def solve() -> None:
    data = sys.stdin.read().split()
    if not data:
        return
    n, k = int(data[0]), int(data[1])
    ans = count_partitions(n, k)
    print(ans)


if __name__ == "__main__":
    solve()
