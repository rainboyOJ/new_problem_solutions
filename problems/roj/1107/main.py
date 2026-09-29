#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-07 09:53
# update_at: 2026-07-07 09:53

import sys


def merge_intervals(intervals: list[tuple[int, int]]) -> list[tuple[int, int]]:
    """按左端点排序后合并所有重叠或相接的区间。"""
    intervals.sort()
    merged: list[tuple[int, int]] = []
    for left, right in intervals:
        if merged and left <= merged[-1][1] + 1:
            merged[-1] = (merged[-1][0], max(merged[-1][1], right))
        else:
            merged.append((left, right))
    return merged


def removed_count(intervals: list[tuple[int, int]]) -> int:
    """计算合并后区间覆盖的整数点个数（含端点）。"""
    return sum(right - left + 1 for left, right in merge_intervals(intervals))


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return
    it = iter(data)
    length = next(it)          # 马路长度 L
    region_count = next(it)    # 区域数 M

    intervals = [(next(it), next(it)) for _ in range(region_count)]
    # 先规范化成左小右大，再用并集长度求被移走的树。
    intervals = [(min(a, b), max(a, b)) for a, b in intervals]
    ans = (length + 1) - removed_count(intervals)
    print(ans)


if __name__ == "__main__":
    solve()
