#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-06 10:00
# update_at: 2026-10-12 14:55

# 扩展二叉树还原：顺序消费扩展先序序列递归建树，再输出中序与后序。
# 扩展先序序列满足「根 + 左子树 + 右子树」的递归结构：遇大写字母就建一个 Node
# 并递归构造左右子树，遇 '.' 就返回 None（空子树）。一个结点的字段收进 Node 对象。
# 如何使用：
# 1. tree = build(iter(s))     # s 是扩展先序序列，tree 是根结点（可能为 None）
# 2. ''.join(inorder(tree))    # 中序序列
# 3. ''.join(postorder(tree))  # 后序序列

import sys
from collections.abc import Iterator


class Node:
    """二叉树的一个结点：字母 + 左右孩子。"""

    def __init__(self) -> None:
        self.label = ''   # 结点上的大写字母
        self.lch = None   # 左孩子，None 表示空子树
        self.rch = None   # 右孩子，None 表示空子树


def build(it: Iterator[str]) -> Node | None:
    """按扩展先序序列递归构造二叉树，None 表示空结点。"""
    c = next(it)
    if c == '.':
        return None
    node = Node()
    node.label = c
    node.lch = build(it)  # 消费掉紧接着的一段，那是左子树
    node.rch = build(it)  # 再往后一段是右子树
    return node


def inorder(t: Node | None) -> Iterator[str]:
    """中序遍历：左 — 根 — 右。"""
    if t:
        yield from inorder(t.lch)
        yield t.label
        yield from inorder(t.rch)


def postorder(t: Node | None) -> Iterator[str]:
    """后序遍历：左 — 右 — 根。"""
    if t:
        yield from postorder(t.lch)
        yield from postorder(t.rch)
        yield t.label


def solve() -> None:
    s = sys.stdin.buffer.read().decode().strip()
    tree = build(iter(s))
    print(''.join(inorder(tree)))
    print(''.join(postorder(tree)))


if __name__ == "__main__":
    solve()
