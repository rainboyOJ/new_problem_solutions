#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 07:06
# update_at: 2026-10-02 07:06

import sys
from itertools import combinations

Item = tuple[int, int, int]   # (价格, 重要度, 归属主件编号，0 表示自己是主件)
Group = list[tuple[int, int]]  # 组首是主件 (价格, 价格x重要度)，其后是它的附件


def build_groups(items: list[Item]) -> list[Group]:
    """把物品按主件分组：主件自开一组，附件挂到 q 指向的主件组尾。"""
    groups: list[Group] = []
    slot: dict[int, Group] = {}  # 主件编号 -> 它的组，附件按 q 查表
    for i, (v, p, q) in enumerate(items, 1):  # 物品编号 1..m，附件的 q 必指向更靠前的主件
        if q == 0:
            slot[i] = [(v, v * p)]
            groups.append(slot[i])
        else:
            slot[q].append((v, v * p))
    return groups


def group_options(group: Group) -> list[tuple[int, int]]:
    """主件组的全部购买方案 (花费, 收益)：必含主件，附件任选子集，不含"整组不买"。"""
    main_v, main_s = group[0]
    atts = group[1:]
    return [
        (main_v + sum(v for v, _ in combo), main_s + sum(s for _, s in combo))  # 一个方案
        for r in range(len(atts) + 1)            # 选 r 个附件，r=0 即只买主件
        for combo in combinations(atts, r)
    ]


def knapsack(plans: list[list[tuple[int, int]]], budget: int) -> int:
    """分组背包：每组至多选一个方案，返回不超过预算的最大收益。"""
    dp = [0] * (budget + 1)
    for opts in plans:
        # 容量倒序遍历：dp[j-cost] 还停在上一组的结果，同组的方案不会被叠加
        for j in range(budget, -1, -1):
            for cost, gain in opts:
                if cost <= j:
                    dp[j] = max(dp[j], dp[j - cost] + gain)
    return max(dp)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    budget, m = next(data), next(data)  # 总钱数、物品件数
    items = [(next(data), next(data), next(data)) for _ in range(m)]
    plans = [group_options(group) for group in build_groups(items)]
    print(knapsack(plans, budget))


if __name__ == "__main__":
    solve()
