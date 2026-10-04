#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 09:26
# update_at: 2026-09-30 09:26

import sys


def max_compatible_activities(intervals: list[tuple[int, int]]) -> int:
    """按结束时间贪心选取尽可能多的互不重叠活动。"""
    count = 0
    last_end = -1
    for start, end in sorted(intervals, key=lambda x: x[1]):
        if start >= last_end:
            count += 1
            last_end = end
    return count


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    try:
        n = next(data)
    except StopIteration:
        return
    intervals = [(next(data), next(data)) for _ in range(n)]
    print(max_compatible_activities(intervals))


if __name__ == "__main__":
    solve()
