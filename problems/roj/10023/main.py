#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 18:14
# update_at: 2026-10-02 18:14

import sys

RESERVE = 100  # 贪心段预留的体积份数：正好是体积上限，误差留给 DP 段修正


def knapsack(items: list[tuple[int, int]], cap: int) -> list[int]:
    """完全背包：f[c] = 体积不超过 c 时的最大价值（正序滚动即每件无限取）。"""
    f = [0] * (cap + 1)
    for a, b in items:
        for j in range(a, cap + 1):
            f[j] = max(f[j], f[j - a] + b)
    return f


def solve() -> None:
    inp = sys.stdin.buffer
    n, m = map(int, inp.readline().split())

    # 同体积只留价值最大的一件：其余同体积物品被它严格支配
    best: list[int] = [0] * 101
    for _ in range(n):
        a, b = map(int, inp.readline().split())
        if b > best[a]:
            best[a] = b

    items = [(a, best[a]) for a in range(1, 101) if best[a]]

    # 密度（价值/体积）最大的物品：任何其它物品换到同体积都换不出更多价值
    a1, b1 = max(items, key=lambda p: p[1] / p[0])

    greedy = max(0, m // a1 - RESERVE)  # 贪心段：先塞满这么多件最优物品
    rest = m - greedy * a1              # DP 段：≤ 100*a1 + 99 ≤ 10099，只算这一小段

    print(greedy * b1 + knapsack(items, rest)[rest])


if __name__ == "__main__":
    solve()
