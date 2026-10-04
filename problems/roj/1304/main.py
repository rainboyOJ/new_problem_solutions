#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 04:05
# update_at: 2026-09-30 04:05

import sys
from functools import cache


@cache
def ways(total: int, parts: int) -> int:
    """把 total 分成 parts 个正整数、不计顺序的方案数。

    parts 份都要非空，所以 total < parts 无解；只剩一份时整块给它，只有 1 种。
    任何方案按「最小值是否为 1」二分：最小值是 1 → 拿掉这个 1，
    剩 ways(total-1, parts-1)；最小值 ≥ 2 → 每份先垫掉 1，整体减 parts，
    一一对应到 ways(total-parts, parts)。两类不重不漏。
    """
    if total < parts:
        return 0
    if parts == 1:
        return 1
    return ways(total - 1, parts - 1) + ways(total - parts, parts)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, k = next(data), next(data)  # 题面只有一组数据，6 < n <= 200，2 <= k <= 6
    print(ways(n, k))


if __name__ == "__main__":
    solve()
