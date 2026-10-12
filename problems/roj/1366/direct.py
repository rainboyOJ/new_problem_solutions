#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 07:15
# update_at: 2026-10-12 15:05
# direct.py：原方法——区间/子串递归直接产出，不显式建结点树（对比新方法见 main.py）。

# 二叉树的凹入表示法：先序 + 中序区间递归，不显式建结点。
# 先序 [pl, pl+n) / 中序 [il, il+n) 就是一棵子树，先序首字符是根，
# 根在中序中的位置把左右子树切开；结点「长度」= 子树叶子数。
# 如何使用：
# 1. read_input()       # 读入先序、中序，建好 pos 表（字符 -> 中序下标）
# 2. walk(0, 0, len)    # 按先序把「字符 × 长度」逐行写进 out
# 3. solve()            # 装配：读入 -> 递归 -> 输出

import sys
from functools import cache

pre = ""                  # 先序遍历序列
ino = ""                  # 中序遍历序列
pos: dict[str, int] = {}  # pos[c] = 字符 c 在中序中的下标
out: list[str] = []       # 输出的每一行


def read_input() -> None:
    """读入先序、中序序列，建好中序下标表。"""
    global pre, ino, pos
    data = iter(sys.stdin.buffer.read().split())
    pre = next(data).decode()
    ino = next(data).decode()
    pos = {c: i for i, c in enumerate(ino)}  # 字符互不重复，中序下标就是唯一切分点


@cache
def length(pl: int, il: int, n: int) -> int:
    """先序 [pl, pl+n) / 中序 [il, il+n) 这棵子树的根的长度。

    长度等于子树里的叶子数：叶为 1，否则左右之和；空子树记 0，
    于是「只有一个孩子」不必分情况，缺失的那侧自然贡献 0。
    """
    if n <= 1:
        return n                              # n == 0 是空子树，n == 1 是叶
    left_n = pos[pre[pl]] - il                # 根在中序的位置 → 左子树大小
    return length(pl + 1, il, left_n) + length(pl + 1 + left_n, pos[pre[pl]] + 1, n - 1 - left_n)


def walk(pl: int, il: int, n: int) -> None:
    """按先序产出整棵子树：先根自己的那一行，再左子树、右子树。"""
    if n == 0:
        return
    left_n = pos[pre[pl]] - il
    out.append(pre[pl] * length(pl, il, n))   # 该结点字母重复「长度」次
    walk(pl + 1, il, left_n)
    walk(pl + 1 + left_n, pos[pre[pl]] + 1, n - 1 - left_n)


def solve() -> None:
    read_input()
    walk(0, 0, len(pre))
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
