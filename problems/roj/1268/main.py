#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 02:38
# update_at: 2026-09-30 02:38

import sys
from itertools import islice


def max_value(items: list[tuple[int, int]], capacity: int) -> int:
    """完全背包：每种物品可取无限多件，返回载重不超过 capacity 时的最大价值。

    best[cap] 表示“前几种物品、容量上限为 cap”时的最大价值。容量正序枚举，使
    best[cap - weight] 读到的是本种物品刚更新过的状态，“再装一件同种物品”因此合法；
    这正是完全背包与 01 背包唯一的实现差别（01 背包必须倒序，保证每种只用一次）。
    """
    best = [0] * (capacity + 1)
    for weight, value in items:
        for cap in range(weight, capacity + 1):
            take = best[cap - weight] + value  # 在本种物品已选若干件的基础上再放一件
            if take > best[cap]:
                best[cap] = take
    return best[capacity]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    capacity, kind_count = next(data), next(data)          # 题面的 M 与 N
    items = list(islice(zip(data, data), kind_count))       # (重量, 价值) 共 N 种
    print(f"max={max_value(items, capacity)}")


if __name__ == "__main__":
    solve()
