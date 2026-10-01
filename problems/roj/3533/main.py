#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 05:51
# update_at: 2026-10-02 05:51

import sys
from heapq import heapify, heappop, heappush


def huffman_total(weights: list[int]) -> int:
    """n-1 次两两合并的最小总代价：每次取当前最小的两堆合并（哈夫曼合并）。"""
    heapify(weights)
    cost = 0
    for _ in range(len(weights) - 1):
        merged = heappop(weights) + heappop(weights)  # 最小的两堆合成新堆
        cost += merged                                # 新堆里的每个果子都要再搬一次
        heappush(weights, merged)
    return cost


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    weights = [next(data) for _ in range(n)]  # 每种果子的数目，即各堆初始重量
    print(huffman_total(weights))


if __name__ == "__main__":
    solve()
