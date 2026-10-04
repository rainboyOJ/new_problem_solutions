#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 07:12
# update_at: 2026-10-02 07:12

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    limit = next(data)  # 每组价格之和的上界 w
    n = next(data)      # 纪念品件数
    prices = sorted(next(data) for _ in range(n))

    # 双指针贪心：最贵的必须和某个最便宜的搭（或独自成组），
    # 因为它和任何更贵的搭都会浪费配额，只可能让组数变多。
    groups = 0
    lo, hi = 0, n - 1
    while lo <= hi:
        if lo < hi and prices[lo] + prices[hi] <= limit:  # 最便宜的能陪最贵的
            lo += 1
        hi -= 1
        groups += 1  # prices[hi] 处理完毕：要么成组，要么落单

    print(groups)


if __name__ == "__main__":
    solve()
