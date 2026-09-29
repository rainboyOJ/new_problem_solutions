#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 02:26
# update_at: 2026-09-30 02:26

import sys
from bisect import bisect_right
from collections.abc import Iterator
from itertools import islice


def read_links(data: Iterator[int], n: int) -> list[tuple[int, int]]:
    """读出 n 对坐标 (南岸, 北岸)，并按南岸坐标升序排列。

    zip(data, data) 复用同一个迭代器，天然把相邻的两个数配成一对。
    """
    return sorted(islice(zip(data, data), n))


def longest_chain(north: list[int]) -> int:
    """求 north 的最长不下降子序列长度。

    tails[k] 记录“长度为 k+1 的不下降子序列”中最小的结尾值，它关于 k 单调不减，
    所以新值 value 接在哪个长度后面可以直接二分。相等也能接（两条航道只是平行不交叉），
    因此插入点取右侧 bisect_right。
    """
    tails: list[int] = []
    for value in north:
        pos = bisect_right(tails, value)
        if pos == len(tails):
            tails.append(value)
        else:
            tails[pos] = value  # 用更小的结尾值换掉旧的，给后面的坐标留出更多空间
    return len(tails)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    links = read_links(data, n)  # 按南岸排序后，问题变成只看北岸的最长不下降子序列
    print(longest_chain([north for _south, north in links]))


if __name__ == "__main__":
    solve()
