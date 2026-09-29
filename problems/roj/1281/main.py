#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 03:02
# update_at: 2026-09-30 03:02

import sys
from bisect import bisect_left


def lis_length(seq: list[int]) -> int:
    """严格上升子序列的最长长度：tails[i] 记录长度 i+1 的最小可能结尾。"""
    tails: list[int] = []
    for value in seq:
        # 等值元素接不上（必须严格上升），故与等值位置交换，保住更小的结尾
        pos = bisect_left(tails, value)
        if pos == len(tails):
            tails.append(value)  # 能延长所有上升子序列
        else:
            tails[pos] = value   # 同长度下结尾更小，后续更容易接
    return len(tails)


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    length = data[0]
    seq = data[1:length + 1]
    print(lis_length(seq))


if __name__ == "__main__":
    solve()
