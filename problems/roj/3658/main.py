#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 13:43
# update_at: 2026-10-02 13:43

import sys
from itertools import pairwise


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    depth = [next(data) for _ in range(n)]

    # 每天只能在"深度非零"的连续段内整体 -1，把每个位置填到 0 的次数里
    # 与左邻共用的部分不会重复计数；答案 = 相邻差分的正部之和。
    ans = sum(max(cur - prev, 0) for prev, cur in pairwise([0] + depth))

    print(ans)


if __name__ == "__main__":
    solve()
