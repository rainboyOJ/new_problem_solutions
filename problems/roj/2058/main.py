#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47
import sys


def post_order(inorder: str, preorder: str) -> str:
    """由中序与前序构造后序遍历字符串：左子树后序 + 右子树后序 + 根。"""
    if not preorder:
        return ""
    root = preorder[0]
    mid = inorder.index(root)
    left_post = post_order(inorder[:mid], preorder[1 : 1 + mid])
    right_post = post_order(inorder[mid + 1 :], preorder[1 + mid :])
    return f"{left_post}{right_post}{root}"


def solve() -> None:
    tokens = sys.stdin.read().split()
    if not tokens:
        return
    inorder, preorder = tokens[0], tokens[1]
    print(post_order(inorder, preorder))


if __name__ == "__main__":
    solve()
