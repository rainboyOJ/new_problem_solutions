#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-10-04 10:36

import sys


def postorder(pre: str, ino: str) -> str:
    """由先序 pre 与中序 ino 递归拼出后序串。

    先序首字符就是根；中序里根左边的 k 个字符是左子树，
    于是两串都能按"前 k 个 / 其余"切开，递归到底即得后序（左 + 右 + 根）。
    """
    if not pre:
        return ''
    k = ino.index(pre[0])  # 根在中序中的位置，也是左子树的结点个数
    return postorder(pre[1:k + 1], ino[:k]) + postorder(pre[k + 1:], ino[k + 1:]) + pre[0]


def solve() -> None:
    data = iter(sys.stdin.read().split())
    pre, ino = next(data), next(data)  # 第一行先序，第二行中序
    print(postorder(pre, ino))


if __name__ == "__main__":
    solve()
