#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 07:28
# update_at: 2026-09-30 07:28

import sys
from heapq import heapify, heappop, heappush
from itertools import islice


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    heaps = list(islice(data, n))          # 每种果子的数目
    heapify(heaps)                         # 小根堆：每次取最小的两堆合并

    cost = 0
    while len(heaps) > 1:                  # 还剩多堆就要再合并一次
        merged = heappop(heaps) + heappop(heaps)  # 最小的两堆合成新堆
        cost += merged                     # 本次体力 = 两堆重量之和
        heappush(heaps, merged)
    print(cost)


if __name__ == "__main__":
    solve()
