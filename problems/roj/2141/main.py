#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 07:52
# update_at: 2026-10-08 07:52

import sys

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Tree = list[list[int]]  # children[u] = u 的所有直接下属


def subtree_sizes(children: Tree, boss: list[int], n: int) -> list[int]:
    """返回每位员工的子树节点数（含本人）。

    先由根 1 得到「父亲排在孩子之前」的 BFS 序，再逆序把每棵子树的大小
    累加给它的上司；逆序保证孩子已经算完，因此不需要递归。
    """
    order = [1]
    for u in order:                # 边遍历边追加，等价于 BFS 队列，根一定在最前
        order += children[u]

    size = [1] * (n + 1)           # 先假设每人都只有自己
    for u in reversed(order[1:]):  # 跳过根：根没有上司可上报
        size[boss[u]] += size[u]
    return size


def solve() -> None:
    tokens = sys.stdin.buffer.read().split()
    if not tokens:                 # 空输入保护
        return

    data = iter(map(int, tokens))  # 顺序消费，避免手算下标偏移
    n = next(data)

    boss = [0] * (n + 1)           # boss[i]：员工 i 的直接上司，根 1 的上司记为 0
    children: Tree = [[] for _ in range(n + 1)]
    for i in range(2, n + 1):
        p = next(data)
        boss[i] = p
        children[p].append(i)

    size = subtree_sizes(children, boss, n)
    print(' '.join(str(s - 1) for s in size[1:]))  # 下属人数 = 子树大小 - 1


if __name__ == "__main__":
    solve()
