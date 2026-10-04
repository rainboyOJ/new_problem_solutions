#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 01:08
# update_at: 2026-09-30 01:11

import sys


def union_span(intervals: list[tuple[int, int]]) -> tuple[int, int] | None:
    """把 n 个区间按左端点升序后单向扫描：返回这 n 个区间的并集闭区间 [left, right]，并集断开则返回 None。

    按左端点升序后只跟踪一个 reach——已并入区间的最大右端点。下一个左端点若越过它，
    中间就出现一段谁也盖不到的空隙，后面的区间左端点只会更大，并集被永久劈开。
    左端点最小者必然排在最左，所以 merged_left 与 reach 的初值取排序后的首行即可。
    """
    ordered = sorted(intervals)
    merged_left, reach = ordered[0]

    for left, right in ordered[1:]:          # 首行已并好，从这里起才不会重复计入自己
        if left > reach:                     # 越过已覆盖范围，中间出现断口
            return None
        reach = max(reach, right)

    return merged_left, reach


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)                           # 题面的 n，3 <= n <= 50000
    intervals = [(next(data), next(data)) for _ in range(n)]

    ans = union_span(intervals)
    print(f"{ans[0]} {ans[1]}" if ans else "no")


if __name__ == "__main__":
    solve()
