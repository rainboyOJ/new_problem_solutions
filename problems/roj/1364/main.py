#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 07:16
# update_at: 2026-09-30 07:16

import sys


def solve() -> None:
    inorder, level = sys.stdin.read().split()             # 中序序列、层序序列
    rank = {ch: i for i, ch in enumerate(level)}         # 每个字符在层序中的排名
    out: list[str] = []

    def preorder(lo: int, hi: int) -> None:
        """递归输出中序区间 [lo, hi) 这棵子树的先序序列。"""
        if lo == hi:
            return
        # 根 = 层序排名最靠前的区间内字符：层序保证祖先一定排在子孙前面
        root = min(inorder[lo:hi], key=rank.__getitem__)
        out.append(root)
        mid = inorder.index(root, lo, hi)                 # 根把中序切成左右子树两段
        preorder(lo, mid)                                 # 左子树区间 [lo, mid)
        preorder(mid + 1, hi)                             # 右子树区间 [mid+1, hi)

    preorder(0, len(inorder))
    print(''.join(out))


if __name__ == "__main__":
    solve()
