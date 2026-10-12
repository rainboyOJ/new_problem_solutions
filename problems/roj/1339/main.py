#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-10-12 14:55

# 由先序 + 中序还原后序：直接在字符串上切片递归，不显式建结点对象。
# 先序串首字符就是根；在中序串里找到根，根左边 k 个字符属于左子树，
# 两串按 k 同步切片，递归到底后按"左子树后序 + 右子树后序 + 根"拼出后序。
# 结点字母互不相同，所以根在中序串中的位置唯一（str.index 不会抛异常）。
# 如何使用：
# 1. postorder(pre, ino)  # 由先序、中序两串递归拼出后序串
# 2. solve()              # 读入先序、中序两行，打印后序一行

import sys


def postorder(pre: str, ino: str) -> str:
    """由先序 pre 与中序 ino 递归拼出后序串（左 + 右 + 根）。"""
    if not pre:
        return ''  # 空子树
    k = ino.index(pre[0])  # 根在中序中的位置，也是左子树的结点个数
    return postorder(pre[1:k + 1], ino[:k]) + postorder(pre[k + 1:], ino[k + 1:]) + pre[0]


def solve() -> None:
    data = iter(sys.stdin.read().split())
    pre, ino = next(data), next(data)  # 第一行先序，第二行中序
    print(postorder(pre, ino))


if __name__ == "__main__":
    solve()
