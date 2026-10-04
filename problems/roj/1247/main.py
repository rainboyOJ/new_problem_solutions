#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 01:32
# update_at: 2026-09-30 01:32

import sys


def need_remove(stones: list[int], mid: int, length: int) -> int:
    """贪心：保证每一段跳跃距离 >= mid 时，最少需要移走的岩石数。

    两处都要删：与上一个保留点距离不足 mid 的岩石；以及越过 limit 的岩石
    （终点跳不了「倒数保留点 -> 终点」这段，必删——终点不可移走）。
    从左往右保留最早可行的岩石，上一个保留点最靠左，后面可选空间最大，故最优。
    """
    limit = length - mid  # 保留点最远只能到 L - mid，否则最后一跳不足 mid
    removed = 0
    last = 0  # 上一个保留点（起点）
    for d in stones:
        if d > limit or d - last < mid:
            removed += 1
        else:
            last = d
    return removed


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    length = next(data)  # 起点到终点的距离 L
    n = next(data)       # 岩石数 N
    m = next(data)       # 最多移走 M 个
    stones = [next(data) for _ in range(n)]  # 输入已按距离升序

    # 答案越大越难满足，对答案二分；need_remove 随 mid 单调不减
    lo, hi = 1, length
    while lo < hi:
        mid = (lo + hi + 1) // 2
        if need_remove(stones, mid, length) <= m:
            lo = mid  # mid 可行，抬高下界
        else:
            hi = mid - 1

    print(lo)


if __name__ == "__main__":
    solve()
