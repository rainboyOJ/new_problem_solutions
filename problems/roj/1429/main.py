#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 09:56
# update_at: 2026-09-30 09:56

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    segments = sorted(((next(data), next(data)) for _ in range(n)), key=lambda s: s[1])  # 按右端点从小到大排序

    # 贪心：每次选右端点最小且与已选不重叠的线段
    count = 0
    last_right = None  # 已选最后一条线段的右端点
    for left, right in segments:
        not_overlap = last_right is None or left >= last_right  # 端点相接不算重合
        if not_overlap:
            count += 1
            last_right = right

    print(count)


if __name__ == "__main__":
    solve()
