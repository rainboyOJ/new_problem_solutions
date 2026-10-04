#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 21:25
# update_at: 2026-09-29 21:25

import sys
from functools import cache


@cache
def sum_to(n: int) -> int:
    """返回 $1+2+\\cdots+n$：边界是 n == 0 时和为 0。"""
    return 0 if n == 0 else n + sum_to(n - 1)  # 未到边界就交给 n-1 层累加


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)  # 题面唯一的整数 N

    print(sum_to(n))


if __name__ == "__main__":
    solve()
