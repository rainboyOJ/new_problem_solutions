#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 20:01
# update_at: 2026-09-30 20:01

import sys
from collections import defaultdict


def tree_dp(children: dict[int, list[int]], joy: list[int], root: int) -> int:
    """树形 DP：相邻两人不能同时选，返回整棵树的最大欢乐度。"""
    # 迭代代替递归：先取"父先于子"的遍历序，再倒序处理，孩子必然先于父亲算完
    order = [root]
    for boss in order:  # 遍历中列表不断变长，恰好把整棵树层展成一列
        order += children[boss]

    dp0 = [0] * len(joy)  # dp0[u]：u 不参加时，u 子树的最优欢乐度
    dp1 = joy[:]          # dp1[u]：u 参加时先记下 u 自己的欢乐度
    for boss in reversed(order):
        for emp in children[boss]:
            dp0[boss] += max(dp0[emp], dp1[emp])  # 上司不来，下属随意
            dp1[boss] += dp0[emp]                 # 上司来了，直接下属都不能来
    return max(dp0[root], dp1[root])  # 根来或不来取大；都不来即空名单，值为 0


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    joy = [0] + [next(data) for _ in range(n)]  # 下标 1..n 对齐员工编号

    # 关系行 "L K"：第 K 人是第 L 人的直接上司；0 0 结束
    children: dict[int, list[int]] = defaultdict(list)
    subordinate = set()
    while True:
        emp, boss = next(data), next(data)
        if emp == 0 and boss == 0:
            break
        children[boss].append(emp)
        subordinate.add(emp)
    # 树根 = 从没当过下属的人
    root = next(u for u in range(1, n + 1) if u not in subordinate)

    print(tree_dp(children, joy, root))


if __name__ == "__main__":
    solve()
