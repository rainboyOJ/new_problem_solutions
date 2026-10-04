#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 02:17
# update_at: 2026-10-01 02:33
#
# 本题面语义（2×N 棋盘用 1×2 骨牌铺满）的参考实现，对应 index.md 的「解法一」。
# 注意：随题测试数据实际考查的是整数划分，提交解必须用 main.py。

import sys


def count_tilings(width: int) -> int:
    """求 2×width 棋盘被 1×2 骨牌铺满的方案数（滚动变量，只保留前两项）。"""
    prev, cur = 1, 1                          # f(0) = 1（空棋盘）、f(1) = 1（竖放一块）
    for _ in range(width):
        prev, cur = cur, prev + cur            # f(i) = f(i-1) + f(i-2)
    return prev


def solve() -> None:
    width = int(sys.stdin.buffer.read().split()[0])   # 题面只说"2×N 的棋盘"，N 是唯一输入
    print(count_tilings(width))


if __name__ == "__main__":
    solve()
