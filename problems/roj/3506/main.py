#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 04:19
# update_at: 2026-10-02 04:19

import sys


def preorder(inorder: str, postorder: str) -> str:
    """由中序 + 后序还原先序：后序末位是根，中序按根切成左右子树递归。"""
    if not postorder:  # 空子树
        return ''
    root = postorder[-1]                       # 后序最后一个一定是子树根
    i = inorder.index(root)                    # 根在中序里的位置 = 左子树大小
    left, right = i, len(inorder) - i - 1
    return root + preorder(inorder[:left], postorder[:left]) \
        + preorder(inorder[left + 1:], postorder[left:left + right])


def solve() -> None:
    lines = sys.stdin.read().split()
    print(preorder(lines[0], lines[1]))


if __name__ == "__main__":
    solve()
