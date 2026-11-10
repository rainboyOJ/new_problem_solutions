#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-11-10 10:55
# update_at: 2026-11-10 10:55

import sys


def max_consecutive_ones(n: int, k: int, a: list[int]) -> tuple[int, list[int]]:
    """用滑动窗口求最多修改 k 个 0 时最长连续 1 的长度及修改后数组。"""
    best_len, best_l = 0, 0
    cnt0 = 0
    l = 0

    # 双指针滑动窗口：右端点逐个纳入，0 超标时左端点收缩
    for r, val in enumerate(a):
        if val == 0:
            cnt0 += 1
        while cnt0 > k:
            if a[l] == 0:
                cnt0 -= 1
            l += 1
        if r - l + 1 > best_len:
            best_len = r - l + 1
            best_l = l

    for i in range(best_l, best_l + best_len):
        a[i] = 1

    return best_len, a


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    token = next(data, None)
    if token is None:
        return
    n = int(token)
    k = int(next(data))
    a = [int(next(data)) for _ in range(n)]

    best_len, res = max_consecutive_ones(n, k, a)
    print(best_len)
    print(" ".join(map(str, res)))


if __name__ == "__main__":
    solve()
