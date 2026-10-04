#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 05:05
# update_at: 2026-09-30 05:05

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    cards = [next(data) for _ in range(n)]

    # 每堆的盈余（正数表示多出来，负数表示还缺）：目标就是让每一堆盈余归零
    diff = [x - sum(cards) // n for x in cards]

    # 前缀和 s[i] = 前 i 堆的盈余之和。相邻两堆之间必须流过的牌数恰好是 |s[i]|，
    # 所以不管怎么调度，第 i 次"跨 i/i+1 边界的移动"都少不了；总次数 = 非零前缀和个数。
    prefix = 0
    moves = 0
    for i in range(n - 1):  # 最后一条边不用管：总盈余为 0，前 n-1 个前缀为 0 即全部为 0
        prefix += diff[i]
        moves += prefix != 0

    print(moves)


if __name__ == "__main__":
    solve()
