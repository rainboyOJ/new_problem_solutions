#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 07:30
# update_at: 2026-09-30 07:30

import sys
from collections.abc import Iterator

# 结点表：下标即输入里的 1-based 结点编号，在 solve() 里按输入顺序填充。
VALUE: list[int] = [0]                # 各结点的值
CHILD: list[tuple[int, int]] = [(0, 0)]  # (左儿子, 右儿子)，0 表示空


def inorder(node: int) -> Iterator[int]:
    """中序遍历：依次产出以 node 为根的子树中的结点编号。"""
    if node:
        yield from inorder(CHILD[node][0])  # 先走左子树
        yield node                          # 再访问根
        yield from inorder(CHILD[node][1])  # 最后走右子树


def solve() -> None:
    data = iter(map(int, sys.stdin.read().split()))
    n = next(data)
    target = next(data)  # 要查找的结点值

    linked: set[int] = set()  # 出现在别人"儿子栏"里的编号
    for _ in range(n):
        v, l, r = next(data), next(data), next(data)
        VALUE.append(v)
        CHILD.append((l, r))
        linked.update((l, r))

    # 根是唯一从未被当作儿子的结点
    root = next(i for i in range(1, n + 1) if i not in linked)

    # 中序序列里的第 i 个结点，名次从 1 开始计
    rank = next(i for i, node in enumerate(inorder(root), 1) if VALUE[node] == target)
    print(rank)


if __name__ == "__main__":
    solve()
