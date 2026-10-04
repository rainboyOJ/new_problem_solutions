#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 20:56
# update_at: 2026-10-01 21:00

import sys
from collections.abc import Iterator


def read_tree(data: Iterator[int], n: int) -> tuple[list[list[int]], int]:
    """读 N-1 行「K 是 L 的直接上司」，返回孩子表和校长编号。"""
    children: list[list[int]] = [[] for _ in range(n + 1)]
    has_boss = bytearray(n + 1)  # 有上司的职员置 1，没被置位的唯一一个就是校长
    for _ in range(n - 1):
        child, boss = next(data), next(data)
        children[boss].append(child)
        has_boss[child] = 1
    return children, next(i for i in range(1, n + 1) if not has_boss[i])


def postorder(children: list[list[int]], root: int) -> Iterator[int]:
    """后序遍历整棵树：最坏是一条 3000 层的链，显式栈比递归稳。"""
    order: list[int] = []
    stack = [root]
    while stack:
        node = stack.pop()
        order.append(node)      # 先父后子地压出顺序
        stack += children[node]
    yield from reversed(order)  # 反过来就是「儿子先于父亲」的后序


def best_happiness(children: list[list[int]], happy: list[int], root: int) -> int:
    """树上最大权独立集：按后序递推每个点的两档状态，返回根节点两档中的较大者。"""
    attend = happy[:]             # attend[v]：v 参会时 v 子树的答案，此时儿子一律不能参会
    absent = [0] * len(happy)     # absent[v]：v 不参会时 v 子树的答案，儿子各自自由取舍
    for node in postorder(children, root):
        for child in children[node]:
            attend[node] += absent[child]                          # f[v][1] += f[儿子][0]
            absent[node] += max(attend[child], absent[child])      # f[v][0] += max(f[儿子][0], f[儿子][1])
    return max(attend[root], absent[root])


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    happy = [0] + [next(data) for _ in range(n)]  # happy[0] 是让下标从 1 开始的占位
    children, root = read_tree(data, n)

    print(best_happiness(children, happy, root))


if __name__ == "__main__":
    solve()
