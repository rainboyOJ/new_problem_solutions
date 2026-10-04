#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-06 10:00
# update_at: 2026-07-06 10:00

import sys
from collections.abc import Iterator


def build(it: Iterator[str]) -> tuple[str, tuple, tuple] | None:
    """按扩展先序序列构造二叉树，None 表示空结点。"""
    c = next(it)
    if c == '.':
        return None
    return (c, build(it), build(it))  # (data, left, right)


def inorder(t) -> Iterator[str]:
    """中序遍历：左根右。"""
    if t:
        yield from inorder(t[1])
        yield t[0]
        yield from inorder(t[2])


def postorder(t) -> Iterator[str]:
    """后序遍历：左右根。"""
    if t:
        yield from postorder(t[1])
        yield from postorder(t[2])
        yield t[0]


def solve() -> None:
    s = sys.stdin.buffer.read().decode().strip()
    tree = build(iter(s))
    print(''.join(inorder(tree)))
    print(''.join(postorder(tree)))


if __name__ == "__main__":
    solve()
