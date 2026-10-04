#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 03:15
# update_at: 2026-10-04 10:24

import sys


def max_sum_rising(seq: list[int]) -> int:
    """f[i]：以 seq[i] 结尾的最大上升子序列和；答案取所有结尾位置里的最大值。"""
    f = [0] * len(seq)
    for i, value in enumerate(seq):
        # 接上"前面严格更小、和最大"的那一段；一个都接不上就自己单独成段
        f[i] = value + max((f[j] for j in range(i) if seq[j] < value), default=0)
    return max(f)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    length = next(data)  # 序列长度 N
    print(max_sum_rising([next(data) for _ in range(length)]))


if __name__ == "__main__":
    solve()
