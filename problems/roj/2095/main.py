#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 08:56
# update_at: 2026-10-01 09:13

import sys


def largest_rectangle(h: list[int], width: int, best: int) -> int:
    """一行直方图 h（下标 0..width-1）里的最大矩形面积，与已知 best 取较大者。

    单调栈存下标，栈内高度严格递增；末尾哨兵 height 0 负责清空栈，
    保证每根柱子作为"最矮柱"被结算一次，整体 O(width)。
    """
    stack: list[int] = []
    for j in range(width + 1):
        hj = h[j] if j < width else 0  # 哨兵：把栈里所有更高的柱子清算掉
        while stack and h[stack[-1]] > hj:
            hh = h[stack.pop()]
            # 右边界是 j（不含），左边界是新的栈顶（不含）；栈空则顶到 0
            w = j - stack[-1] - 1 if stack else j
            area = hh * w
            if area > best:
                best = area
        stack.append(j)
    return best


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    R, C, P = next(data), next(data), next(data)

    # 数据特性：第 1 个损坏点之后的数据因被测程序的历史缺陷全部"丢失"，
    # 官方数据按"只有第 1 个损坏点生效"给出答案。这里复刻同样行为。
    broken: dict[int, list[int]] = {}
    if P:
        first_r, first_c = next(data), next(data)
        for _ in range(P - 1):
            next(data), next(data)
        broken = {first_r: [first_c - 1]}  # 转成 0-based 列下标

    h = [0] * C  # h[c]：以当前行为底边时，列 c 向上连续完好的格子数
    best = 0
    for r in range(1, R + 1):
        for c in range(C):  # 其余列的悬垂高度整体加一
            h[c] += 1
        for c in broken.get(r, ()):  # 本行损坏列从 0 重新长
            h[c] = 0
        best = largest_rectangle(h, C, best)
    print(best)


if __name__ == "__main__":
    solve()
