#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 07:30
# update_at: 2026-10-12 14:36

# 树的存储：父亲孩子表示法（二叉树特化）
# 一个结点的四个字段聚合成 Node 对象：值、左儿子、右儿子、父亲，
# 对应文章模板里的 val/lch/rch/fa 四个全局列表，这里收进同一个对象。
# 如何使用：
# 1. init(n)                     # 多组数据必须调用
# 2. 读入第 i 行：node[i].value/lch/rch 赋值，顺手 node[儿子].fa = i
# 3. 向下：node[u].lch / node[u].rch；向上：node[u].fa；根就是 fa == 0 的点

import sys
from collections.abc import Iterator


class Node:
    """编号 u 的结点：值 + 左右孩子 + 父亲（父亲孩子表示法的二叉树特化）。"""

    def __init__(self) -> None:
        self.value = 0  # 结点的值
        self.lch = 0    # 左儿子编号，0 表示空
        self.rch = 0    # 右儿子编号，0 表示空
        self.fa = 0     # 父亲编号；fa == 0 表示这个点是根


node: list[Node] = []  # node[u]：编号 u 的结点


def init(n: int) -> None:
    """造出 0..n 共 n+1 个结点，字段全为 0（fa == 0 正好表示"根没有父亲"）。"""
    global node
    node = [Node() for _ in range(n + 1)]


def find_root(n: int) -> int:
    """根是唯一没当过儿子的点：读入时每个儿子都写了 fa，所以 fa == 0 的就是根。"""
    return next(i for i in range(1, n + 1) if node[i].fa == 0)


def inorder(u: int) -> Iterator[int]:
    """中序遍历：左子树 -> 根 -> 右子树，依次产出结点编号。"""
    if u:
        yield from inorder(node[u].lch)  # 先走左子树
        yield u                          # 再访问根
        yield from inorder(node[u].rch)  # 最后走右子树


def solve() -> None:
    data = iter(map(int, sys.stdin.read().split()))
    n = next(data)
    target = next(data)  # 要查找的结点值

    init(n)
    for i in range(1, n + 1):
        v, l, r = next(data), next(data), next(data)
        node[i].value = v
        node[i].lch = l
        node[i].rch = r
        # 孩子一登记，父亲也顺手记下：这一步就把 fa 填好了
        if l:
            node[l].fa = i
        if r:
            node[r].fa = i

    # 中序序列里第 i 个结点的名次从 1 开始数
    rank = next(i for i, u in enumerate(inorder(find_root(n)), 1) if node[u].value == target)
    print(rank)


if __name__ == "__main__":
    solve()
