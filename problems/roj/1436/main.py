#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys


def count_segments(a: list[int], limit: int) -> int:
    """上限为 limit 时最少分几段：贪心累加，放不下就另起一段。"""
    segments, cur = 1, 0
    for x in a:
        cur_add = cur + x
        if cur_add <= limit:
            cur = cur_add                        # 还塞得进当前段
        else:
            segments += 1                        # 另起一段
            cur = x
    return segments


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    a = [next(data) for _ in range(n)]

    # 答案 x 的判定具有单调性：x 越大，最少段数越少，在 [max(a), sum(a)] 上二分
    lo, hi = max(a), sum(a)                      # 每段至少装下最大元素；最多一段装下全部
    while lo < hi:
        mid = (lo + hi) // 2
        can = count_segments(a, mid) <= m        # 上限 mid 时段数不超限 → 答案 ≤ mid
        if can:
            hi = mid
        else:
            lo = mid + 1

    print(lo)


if __name__ == "__main__":
    solve()
