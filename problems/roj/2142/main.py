#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 11:30
# update_at: 2026-10-12 14:52

# 树的最大匹配：自底向上贪心——儿子都决策完后，u 与父亲都还空着就配掉父边。
# 一个结点的字段聚合成 Node 对象：父亲编号 + 是否已被匹配边占用，
# 对应 fa[] / matched[] 两个平行列表，这里收进同一个对象。
# 如何使用：
# 1. init(n)          造出 0..n 共 n+1 个结点和空邻接表
# 2. add_edge(a, b)   n-1 条边两个方向都存，BFS 时才走得通
# 3. bfs_order()      以 1 为根求"父亲先于儿子"的序（显式队列，不递归）
# 4. greedy_match()   倒着扫序做贪心配对，返回匹配边数
# 注意：n = 2e5 的链形数据会让递归 DFS 爆栈，所以全程用显式队列。

import sys


class Node:
    """编号 u 的结点：父亲 + 是否已被匹配边占用。"""

    def __init__(self) -> None:
        self.fa = 0          # 父亲编号，根的父亲是 0
        self.matched = False # 是否已经被某条匹配边占用


node: list[Node] = []     # node[u]：编号 u 的结点
adj: list[list[int]] = [] # adj[u]：u 的邻接表（无向树）


def init(n: int) -> None:
    """造出 0..n 共 n+1 个结点和空邻接表。"""
    global node, adj
    node = [Node() for _ in range(n + 1)]
    adj = [[] for _ in range(n + 1)]


def add_edge(u: int, v: int) -> None:
    """加一条无向边：树边两个方向都要存。"""
    adj[u].append(v)
    adj[v].append(u)


def bfs_order() -> list[int]:
    """以 1 为根做迭代 BFS，返回"父亲先于儿子"的访问序 order。

    边遍历边追加：list 迭代会看到新元素，order 自己就是队列。
    显式队列而非递归，避免 n = 2e5 的链形数据爆栈。
    """
    order = [1]
    node[1].fa = 0
    for u in order:
        for v in adj[u]:
            if v != node[u].fa:  # 树上唯一的已访邻点就是父亲
                node[v].fa = u
                order.append(v)
    return order


def greedy_match(order: list[int]) -> int:
    """自底向上贪心：倒着扫 order，u 与父亲都还空着就配 (u, fa[u])。

    u 被处理时它的所有儿子都已决策完；交换论证保证这样不会比最优解差。
    """
    ans = 0
    for u in reversed(order):
        p = node[u].fa
        if p and not node[u].matched and not node[p].matched:
            node[u].matched = node[p].matched = True
            ans += 1
    return ans


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    try:
        n = next(data)
    except StopIteration:  # 空输入
        return

    init(n)
    for _ in range(n - 1):
        a, b = next(data), next(data)
        add_edge(a, b)

    print(greedy_match(bfs_order()))


if __name__ == "__main__":
    solve()
