#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 12:15
# update_at: 2026-10-01 12:20

import sys

FREE = b'F'  # 输入里表示"这块地归 freda"的字符，只有它能拼出目标矩形


def max_histogram_area(heights: list[int]) -> int:
    """单调栈求直方图最大矩形：栈里存下标，对应高度从栈底到栈顶严格递增。"""
    stack: list[int] = []                     # 栈顶是当前柱子的左边界来源
    best = 0
    for i, h in enumerate(heights + [0]):      # 末尾补高度 0 的哨兵，收尾时把栈弹空
        while stack and heights[stack[-1]] >= h:
            left = stack.pop()
            # 弹掉 left 后：新栈顶是左边第一个更矮的柱子，i 是右边第一个更矮的柱子
            width = i - (stack[-1] if stack else -1) - 1
            best = max(best, heights[left] * width)
        stack.append(i)
    return best


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n, m = int(next(data)), int(next(data))

    heights: list[int] = [0] * m  # heights[j] = 以当前行为底，第 j 列向上连续的 'F' 个数
    answer = 0
    for _ in range(n):
        row = [next(data) for _ in range(m)]  # 逐行顺序消费 m 个格子字符
        heights = [h + 1 if cell == FREE else 0 for h, cell in zip(heights, row)]
        answer = max(answer, max_histogram_area(heights))  # 枚举矩形的下边界所在行

    print(answer * 3)  # 题面要求输出 3 * 最大面积


if __name__ == "__main__":
    solve()
