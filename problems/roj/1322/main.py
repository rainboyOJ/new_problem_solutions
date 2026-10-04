#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 05:06
# update_at: 2026-09-30 05:06

import sys
from bisect import bisect_left


def min_systems(heights: list[int]) -> int:
    """拦截全部导弹最少需要的系统数 = 最长严格上升子序列长度（Dilworth 定理）。

    tails[k] 表示"长度为 k+1 的严格上升子序列"目前能取到的最小结尾高度，
    它整体单调递增，所以每个新高度都能用二分找到归宿。
    """
    tails: list[int] = []
    for h in heights:
        pos = bisect_left(tails, h)  # 第一个 >= h 的位置：能接上就变长，接不上就换掉结尾
        tails[pos:pos + 1] = [h]     # pos == len(tails) 时切片赋值等价于 append
    return len(tails)


def solve() -> None:
    heights = list(map(int, sys.stdin.buffer.read().split()))  # 依次飞来的高度，读到 EOF

    print(min_systems(heights))


if __name__ == "__main__":
    solve()
