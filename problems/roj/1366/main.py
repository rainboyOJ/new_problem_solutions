#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 07:15
# update_at: 2026-10-04 11:25

import sys
from functools import cache


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    pre = next(data).decode()                       # 先序串
    ino = next(data).decode()                       # 中序串
    pos = {c: i for i, c in enumerate(ino)}  # 字符互不重复，中序下标就是唯一切分点
    out: list[str] = []

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

    walk(0, 0, len(pre))
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
