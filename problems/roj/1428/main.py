#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 09:43
# update_at: 2026-09-30 09:43

import sys


def min_segments(seq: list[int], max_sum: int) -> int:
    """计算将序列划分为每段和不超过 max_sum 的最少段数。"""
    count = 1
    current_sum = 0
    for x in seq:
        if current_sum + x <= max_sum:
            current_sum += x
        else:
            count += 1
            current_sum = x
    return count


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    try:
        n = next(data)
    except StopIteration:
        return
    m = next(data)
    seq = [next(data) for _ in range(n)]

    ans = min_segments(seq, m)
    print(ans)


if __name__ == "__main__":
    solve()
