#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 07:30
# update_at: 2026-10-12 14:52

# 二叉树的顺序存储判对称：位置 k 的左右孩子固定在 2k+1 / 2k+2
# 串里 s[k] 是位置 k 的结点字母，'#' 是空位。把串补到 2n 长后，
# 相邻位置 (1,2)、(3,4)、... 恰好是一对对兄弟；
# 每对兄弟"同空或同非空" <=> "每个结点要么没孩子、要么孩子齐全"，就是题目的对称定义。
# 如何使用：
# 1. pad_tail(s)     末尾省略的孩子补成 '#'，只多出"同空"兄弟对，不影响判定
# 2. is_symmetric(s) 逐对兄弟检查，出现"一空一非空"就返回 False
# 3. solve()         读入 -> 补尾 -> 判定，输出 Yes / No

import sys

EMPTY = '#'             # 顺序存储里的空位置标记
BOTH_EMPTY = EMPTY * 2  # 一对兄弟都为空的样子


def pad_tail(level_order: str) -> str:
    """把串补到 2n 长：末尾省略不写的孩子补成空位。"""
    return level_order.ljust(len(level_order) * 2, EMPTY)


def is_symmetric(level_order: str) -> bool:
    """逐对兄弟检查：(2k+1, 2k+2) 是结点 k 的两个孩子，同空或同非空才对称。"""
    padded = pad_tail(level_order)
    # 兄弟对要么都为空，要么都非空；出现"一空一非空"就存在只有一个孩子的结点
    return all(padded[i:i + 2] == BOTH_EMPTY or EMPTY not in padded[i:i + 2]
               for i in range(1, len(level_order), 2))


def solve() -> None:
    level_order = sys.stdin.read().strip()
    print('Yes' if is_symmetric(level_order) else 'No')


if __name__ == "__main__":
    solve()
