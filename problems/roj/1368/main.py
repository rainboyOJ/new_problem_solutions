#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 07:30
# update_at: 2026-09-30 07:30

import sys

EMPTY = '#'   # 顺序存储里的空位置标记
BOTH_EMPTY = EMPTY * 2  # 一对兄弟都为空的样子


def is_symmetric(level_order: str) -> bool:
    """顺序存储的二叉树是否对称：每个结点要么没孩子，要么孩子齐全。

    顺序存储把结点按层从左到右排开，根占位置 0，其后依次是各结点的两个孩子。
    于是位置 1、2 是根的孩子，3、4 是下一个结点的孩子……每两个相邻位置
    (2k+1, 2k+2) 恰好是一对兄弟。只要某一对里一个为空、另一个非空，
    就存在只有一个孩子的结点，答案为 No；所有兄弟对都「同空或同非空」才对称。
    末尾的孩子常省略不写，补上空位只会多出「同空」的兄弟对，不影响结论。
    """
    length = len(level_order)
    padded = level_order.ljust(length * 2, EMPTY)
    return all(padded[i:i + 2] == BOTH_EMPTY or EMPTY not in padded[i:i + 2]
               for i in range(1, length, 2))  # 兄弟同空，或都非空


def solve() -> None:
    level_order = sys.stdin.read().strip()
    print('Yes' if is_symmetric(level_order) else 'No')


if __name__ == "__main__":
    solve()
