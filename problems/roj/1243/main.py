#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 01:19
# update_at: 2026-09-30 01:19

import sys
from collections.abc import Iterator


def feasible(limit: int, a: list[int], m: int) -> bool:
    """能否把 a 分成不超过 m 段，使每段和都不超过 limit。"""
    parts = 1          # 当前段数
    total = 0          # 当前累计和
    for x in a:
        if x > limit:  # 单日超限，直接不可行
            return False
        if total + x <= limit:
            total += x
        else:
            parts += 1
            total = x
            if parts > m:
                return False
    return True


def solve() -> None:
    data = map(int, sys.stdin.buffer.read().split())
    it: Iterator[int] = iter(data)
    n = next(it)
    m = next(it)
    a = [next(it) for _ in range(n)]

    lo, hi = max(a), sum(a)
    while lo < hi:
        mid = (lo + hi) // 2
        if feasible(mid, a, m):
            hi = mid
        else:
            lo = mid + 1
    print(lo)


if __name__ == "__main__":
    solve()
