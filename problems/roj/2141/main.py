#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 07:52
# update_at: 2026-10-12 14:53

# 公司继承树：父亲孩子表示法 + BFS 序自底向上求子树大小
# 一个员工的三个字段聚合成 Node 对象：直接上司、全部直接下属、子树大小。
# 如何使用：
# 1. 读入员工 i 的上司 p：node[i].boss = p，node[p].child.append(i)
# 2. 从总经理 1 求 BFS 序（父亲先于孩子入队），逆序处理就是"孩子先算完"
# 3. 员工 i 的下属人数 = node[i].sz - 1（去掉本人）
# 注意：上司编号不保证小于本人编号，不能按编号倒着扫，必须用 BFS 序。

import sys
from collections.abc import Iterator


class Node:
    """员工 u：直接上司 + 全部直接下属 + 子树大小（含本人）。"""

    def __init__(self) -> None:
        self.boss = 0               # 直接上司编号，总经理 1 的上司记为 0
        self.child: list[int] = []  # 全部直接下属编号
        self.sz = 1                 # 以 u 为根的子树大小（含本人）


node: list[Node] = []  # node[u]：员工 u


def init(n: int) -> None:
    """造出 0..n 共 n+1 个员工，子树大小都先算作 1（只有自己）。"""
    global node
    node = [Node() for _ in range(n + 1)]


def build_order(n: int) -> list[int]:
    """从总经理 1 出发求 BFS 序：入队时父亲一定先于孩子，可以当拓扑序用。"""
    order = [1]
    for u in order:      # 边遍历边追加，等价于 BFS 队列，根一定在最前
        order += node[u].child
    return order


def calc_subtree_size(n: int) -> None:
    """逆着 BFS 序自底向上累加：孩子一定先算完，再把自己整棵子树报给上司。"""
    order = build_order(n)
    for u in reversed(order[1:]):  # 跳过根：根没有上司可上报
        node[node[u].boss].sz += node[u].sz


def solve() -> None:
    tokens = sys.stdin.buffer.read().split()
    if not tokens:  # 空输入保护
        return

    data: Iterator[int] = iter(map(int, tokens))
    n = next(data)

    init(n)
    for i in range(2, n + 1):
        p = next(data)
        node[i].boss = p
        node[p].child.append(i)  # 建边：上司 -> 直接下属

    calc_subtree_size(n)
    print(' '.join(str(node[i].sz - 1) for i in range(1, n + 1)))  # 下属人数 = 子树大小 - 1


if __name__ == "__main__":
    solve()
