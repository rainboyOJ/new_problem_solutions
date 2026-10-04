#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 02:52
# update_at: 2026-09-30 02:52

import sys


def add_group(dp: list[int], group: list[tuple[int, int]], capacity: int) -> list[int]:
    """把一组互斥物品并入 dp，返回合并后的新价值表。

    dp[cap] 表示容量不超过 cap 时的最大价值，且只统计已处理完的组。
    新表的每个格子只读旧表：不选这一组（旧值 dp[cap]），或从旧表挑组内一件物品，
    所以组内任意两件物品都不可能在同一个格子里叠加，天然满足「最多选一件」。
    """
    # picks[cap]：这一组选某一件物品后能达到的价值；只查旧表（上一轮 dp），绝不同时查组内另一件
    picks = [
        [dp[cap - weight] + value for weight, value in group if weight <= cap]
        for cap in range(capacity + 1)
    ]
    return [max([old, *options]) for old, options in zip(dp, picks)]  # old = 这一组一件都不选


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    capacity, item_count, group_count = next(data), next(data), next(data)

    groups: list[list[tuple[int, int]]] = [[] for _ in range(group_count + 1)]
    for _ in range(item_count):
        weight, value, group = next(data), next(data), next(data)
        groups[group].append((weight, value))

    dp = [0] * (capacity + 1)
    for group in groups[1:]:
        dp = add_group(dp, group, capacity)

    print(dp[capacity])  # dp[cap] 单调不减，容量上限处就是答案


if __name__ == "__main__":
    solve()
