#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 03:27
# update_at: 2026-09-30 03:27

import sys
from bisect import bisect_left


def lis_length(seq: list[int]) -> int:
    """严格上升子序列的最大长度：tails[L-1] 是长度 L 的子序列的最小可能结尾。"""
    tails: list[int] = []
    for value in seq:
        pos = bisect_left(tails, value)  # 第一个 >= value 的位置，也就是该值能顶替的最短长度
        if pos == len(tails):
            tails.append(value)          # 比所有层的结尾都大，可以再加一层
        else:
            tails[pos] = value           # 同长度换成更小的结尾，后续更容易接上
    return len(tails)


def best_glide(heights: list[int]) -> int:
    """一次单向滑翔最多经过的建筑数：起点任选、方向任选，但只能飞向更低的建筑。"""
    rightward = [-h for h in heights]                 # 向右滑：下标递增而高度递减，取负变递增
    leftward = [-h for h in reversed(heights)]        # 向左滑：时间倒放，等价于反转序列后同法计算
    return max(map(lis_length, (rightward, leftward)))  # 两个方向互相独立，取更优者


def solve() -> None:
    it = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []

    case_count = next(it)                # 题面的 K
    for _ in range(case_count):
        building_count = next(it)        # 题面的 N
        heights = [next(it) for _ in range(building_count)]
        out.append(str(best_glide(heights)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
