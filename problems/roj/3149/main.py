#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 21:08
# update_at: 2026-10-01 21:20

import sys
from collections.abc import Iterator

NEG = -10**9  # 「这个门数凑不出来」的哨兵；学分都是正整数，不会和真实答案混淆


def read_courses(data: Iterator[int], n: int) -> tuple[list[list[int]], list[int]]:
    """读 N 行「先修课 学分」，返回孩子表与学分表（课程编号 1..N）。

    「每门课的直接先修课最多只有一门」意味着 {先修课 -> 本课} 是一张森林；
    把虚拟根 0 当成所有无先修课的课的父亲，森林就变成以 0 为根的树。
    """
    children: list[list[int]] = [[] for _ in range(n + 1)]
    credits: list[int] = [0] * (n + 1)
    for course in range(1, n + 1):
        prereq = next(data)              # 本课的直接先修课，0 表示没有
        credits[course] = next(data)
        children[prereq].append(course)  # 先修课就是父亲
    return children, credits


def postorder(children: list[list[int]], root: int) -> Iterator[int]:
    """后序遍历整棵树：显式栈先压出「父在子前」的序列，反转就是「子在父前」。"""
    order: list[int] = []
    stack = [root]
    while stack:
        node = stack.pop()
        order.append(node)
        stack += children[node]
    yield from reversed(order)


def best_credits(children: list[list[int]], credits: list[int], m: int) -> int:
    """树上背包：dp[v][j] = 在 v 的子树里选 j 门课（必含 v）能拿到的最高学分。

    先修关系要求「选一门课就得选它的先修课」，于是 v 被选了，儿子们才有资格选；
    反过来，儿子子树之间互不影响，可以用「按门数合并」的背包式子拼起来。
    虚拟根 0 也占一门课的预算，所以总预算取 M+1，答案落在 dp[0][M+1]。
    """
    budget = m + 1
    dp: list[list[int]] = [[] for _ in range(len(children))]
    subtree = [0] * len(children)  # 子树节点数被 min(·, budget) 封顶，用于裁剪背包循环
    for node in postorder(children, 0):
        best = [NEG] * (budget + 1)
        best[1] = credits[node]  # 先备好「只选 node 自己」这一档
        used = 1                 # 已合并部分最多能贡献的门数
        for child in children[node]:
            sub, sub_cap = dp[child], min(subtree[child], budget)
            for j in range(min(used, budget), 0, -1):  # j 倒序扫，避免同一个儿子被选两次
                if best[j] == NEG:
                    continue
                for k in range(1, min(sub_cap, budget - j) + 1):
                    cand = best[j] + sub[k]
                    if cand > best[j + k]:
                        best[j + k] = cand
            used = min(used + sub_cap, budget)
        subtree[node] = used
        dp[node] = best
    return dp[0][budget]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    children, credits = read_courses(data, n)

    print(best_credits(children, credits, m))


if __name__ == "__main__":
    solve()
