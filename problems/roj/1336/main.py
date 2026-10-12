#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 05:56
# update_at: 2026-10-12 14:53

# 树的存储：父亲孩子表示法（每个结点记父亲 + 孩子列表）
# 一个结点的两个字段聚合成 Node 对象：父亲、孩子列表。
# 如何使用：
# 1. 读入每条边 (x, y)：node[y].fa = x，node[x].child.append(y)
# 2. 根是唯一 fa == 0 的结点；孩子最多的结点取 child 最长者，并列取编号小的
# 3. 输出它的孩子前先排序——输入不保证有序

import sys
from collections.abc import Iterator

MAXN = 1005  # 题面结点编号 x,y <= 1000，按上界开


class Node:
    """编号 u 的结点：父亲 + 全部孩子（父亲孩子表示法）。"""

    def __init__(self) -> None:
        self.fa = 0               # 父亲编号，fa == 0 表示还没有人认领它（即根）
        self.child: list[int] = []  # 全部孩子编号，输入不保证有序


node: list[Node] = [Node() for _ in range(MAXN)]  # node[u]：编号 u 的结点


def pairs(nums: Iterator[int]) -> Iterator[tuple[int, int]]:
    """把 2m 个结点编号按 (父结点, 孩子) 两两成对。"""
    return zip(nums, nums)


def find_root(n: int) -> int:
    """根是唯一没当过孩子的点：读入时每个孩子都写了 fa，所以 fa == 0 的就是根。"""
    return next(i for i in range(1, n + 1) if node[i].fa == 0)


def find_busiest(n: int) -> int:
    """孩子最多的结点，并列取编号小者：max 只保留第一个最大值，
    而 range 递增，所以并列时自然取到编号小的结点。"""
    return max(range(1, n + 1), key=lambda v: len(node[v].child))


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    # 每行的 y 是 x 的孩子：x 的孩子表多一条，y 认下父亲 x
    for x, y in pairs(data):
        node[y].fa = x
        node[x].child.append(y)

    busiest = find_busiest(n)
    print(find_root(n))
    print(busiest)
    print(*sorted(node[busiest].child))  # 输出要求升序，输入不保证有序


if __name__ == "__main__":
    solve()
