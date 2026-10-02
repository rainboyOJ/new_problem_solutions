#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 19:28
# update_at: 2026-10-02 19:28

import sys
from functools import cmp_to_key


def by_ratio(a: tuple[int, int], b: tuple[int, int]) -> int:
    """按脾气比 t_i/c_i 升序比较：交叉相乘，避免除法和 c_i=0 的除零。"""
    return a[0] * b[1] - b[0] * a[1]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    fish = [(next(data), next(data)) for _ in range(n)]  # 每条鱼 (t_i, c_i)
    fish.sort(key=cmp_to_key(by_ratio))  # 相邻逆序交换只会更优，故按比值排序即最优

    elapsed = 0  # 当前时刻：前面所有鱼往返耗时之和
    cost = 0
    for take, temper in fish:
        cost += elapsed * temper  # 此刻开始运的体力 = 时刻 × 脾气（第一条体力 0）
        elapsed += take * 2       # 运一条鱼要往返，耗时 2*t_i

    print(cost)


if __name__ == "__main__":
    solve()
