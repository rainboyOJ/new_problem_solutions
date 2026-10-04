#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 19:38
# update_at: 2026-09-29 19:38

import sys
from itertools import groupby


def longest_plateau(seq: list[int]) -> int:
    """本题要求的最长平台长度：groupby 只把「相邻且相等」的元素归入同一组。"""
    return max((len(list(group)) for _, group in groupby(seq)), default=0)


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    n = data[0]  # 题面的 n，只用来界定数组范围
    seq = data[1:1 + n]
    print(longest_plateau(seq))


if __name__ == "__main__":
    solve()
