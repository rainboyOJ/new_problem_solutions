#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-03 10:12
# update_at: 2026-10-03 10:12

import sys
from bisect import bisect_left, bisect_right


def lis_length(a: list[int], strict: bool) -> int:
    """求序列 a 的最长(严格/不严格)上升子序列长度。

    tails[i] 是所有长度为 i+1 的上升子序列末尾元素的最小值，
    它严格递增（或至少不降），所以每步可以二分。strict 为 False 时
    求"不下降"版本：末尾相等也可延长，用 bisect_right 接到同值 tails 的右边。
    """
    tails: list[int] = []  # 长度为 i+1 的子序列的最小末尾
    for h in a:
        pos = bisect_right(tails, h) if strict else bisect_left(tails, h)
        if pos == len(tails):
            tails.append(h)  # 能接成一条更长的子序列
        else:
            tails[pos] = h  # 把最小末尾再压低，给后面的元素留更多机会
    return len(tails)


def solve() -> None:
    heights = list(map(int, sys.stdin.buffer.read().split()))  # 导弹依次飞来的高度

    # 第一问：一套系统每发不能高于前一发 → 最长不升子序列。
    # 把序列翻转后，"从左到右不升"恰好变成"从右到左不降"，等价于求翻转序列的最长不降子序列。
    best_one = lis_length(heights[::-1], strict=False)

    # 第二问：Dilworth 定理——把全序集划分成最少条"不升链"的数目，等于最长严格上升子序列的长度。
    best_split = lis_length(heights, strict=True)

    print(best_one)
    print(best_split)


if __name__ == "__main__":
    solve()
