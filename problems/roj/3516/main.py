#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 04:52
# update_at: 2026-10-02 04:52

import sys


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    n = data[0]
    piles = data[1:n + 1]
    avg = sum(piles) // n  # 每堆最终张数：总数必为 n 的倍数

    # 贪心：1 号堆只能把牌推给 2 号，其差额必须一次搬完；搬完后 1 号永久定型。
    # 依次处理到 n-1 号，每堆不等于 avg 就做一次移动，把差额整体推给右邻。
    moves = 0
    for i in range(n - 1):
        if piles[i] != avg:
            moves += 1                       # 一次移动可搬任意张数，只计次数
            piles[i + 1] += piles[i] - avg   # 右邻接管差额，本堆定型为 avg
    print(moves)


if __name__ == "__main__":
    solve()
