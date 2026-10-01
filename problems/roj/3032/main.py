#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 11:16
# update_at: 2026-10-01 11:20

import sys
from itertools import chain


def max_rect(heights: list[int]) -> int:
    """返回柱状图（每根宽 1、公共基线对齐）中最大轴对齐矩形的面积。

    单调栈从底到顶按高度严格递增地存下标。弹出栈顶 j 时，新栈顶 left 是 j 左边
    第一个更矮的柱子，而当前位置 right 是 j 右边第一个更矮的柱子；所以高度
    取 heights[j] 的矩形最远只能铺满开区间 (left, right)，宽度恰好 right-left-1。
    追加一个高度 0 的哨兵（下标 n）收尾，保证每根柱子都被弹出且只结算一次。
    """
    stack: list[int] = []  # 只存下标
    best = 0
    for right, height in enumerate(chain(heights, (0,))):
        while stack and height <= heights[stack[-1]]:
            popped = stack.pop()
            left = stack[-1] if stack else -1  # 左侧第一个更矮的柱子，-1 表示没有更矮的
            best = max(best, heights[popped] * (right - left - 1))
        stack.append(right)
    return best


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    # 每个测试用例以 n 打头：n 是这组柱子的根数，n=0 是结束标记、不用处理
    for n in data:
        if n == 0:
            break
        out.append(str(max_rect([next(data) for _ in range(n)])))
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
