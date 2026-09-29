#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 03:41
# update_at: 2026-09-30 03:41

import sys
from itertools import islice


def count_subsets(values: list[int], target: int) -> int:
    """选出若干个数使和恰为 target 的组合数（选哪几个数，不计选取顺序）。

    ways[s] 是「已处理的那批数里，和恰为 s 的组合数」。每个数只允许用一次，
    所以每轮更新必须写成同时取旧值的 new = old + 错位后的 old：切片右侧在赋值前
    已全部求值，zip 读到的旧 ways 不会混入本轮刚写的结果（等价于倒序枚举）。
    """
    ways = [1] + [0] * target  # ways[0] = 1：一个数都不选，和恰为 0
    for value in values:
        ways[value:] = [take + skip for take, skip in zip(ways[value:], ways)]
    return ways[target]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    count, target = next(data), next(data)          # 题面的 n 与 t
    values = list(islice(data, count))
    print(count_subsets(values, target))


if __name__ == "__main__":
    solve()
