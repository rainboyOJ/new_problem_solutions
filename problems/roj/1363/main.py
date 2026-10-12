#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 07:16
# update_at: 2026-10-12 14:55

# 满二叉树小球下落：不建树、不模拟布尔标记，奇偶折半直接定位叶子。
# 所有球都经过根，第 I 个球就是第 I 个到达根的球；第 j 个到达某结点的球，
# j 为奇数走左、偶数走右，走左的球占前一半序号、走右的占后一半。
# 所以只需跟踪"第几个球在当前子树里的序号"，逐层折半，走 depth-1 层即落在叶子上。
# 如何使用：
# 1. leaf_of(depth, index)  # 第 index 个小球停下的叶子序号（满二叉树按层序编号）
# 2. solve()                # 读入一行 D I，打印叶子序号

import sys


def leaf_of(depth: int, index: int) -> int:
    """第 index 个小球停下的叶子序号：每层用 index 的奇偶定方向，再把 index 折半。"""
    node = 1
    for _ in range(depth - 1):  # 从根往下走 depth-1 层到达叶子
        go_left = index & 1  # 该结点第奇数次被访问的球走左，偶数次走右
        node = 2 * node + (1 - go_left)  # 左孩子 2k、右孩子 2k+1
        index = (index + go_left) >> 1  # 走左的球挤进前一半序号，走右的落到后一半
    return node


def solve() -> None:
    depth, index = map(int, sys.stdin.buffer.read().split())
    print(leaf_of(depth, index))


if __name__ == "__main__":
    solve()
