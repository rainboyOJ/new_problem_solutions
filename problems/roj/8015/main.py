#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 17:00
# update_at: 2026-10-02 17:00

import sys


def best_keep(prices: list[int]) -> int:
    """最多能保留多少个纪念品：以每个下标结尾的最长合法子序列（类 LIS）。"""
    keep = [1] * len(prices)  # keep[i]：一定保留第 i 个纪念品时，最多保留多少个
    for i, price in enumerate(prices):
        # 保留的第 j 个在 i 前面，且它接到 i 身边时差值不为 1，才能转移
        keep[i] = 1 + max(
            (keep[j] for j, prev in enumerate(prices[:i]) if abs(price - prev) != 1),
            default=0,  # 前面一个都接不上时，只保留 i 自己
        )
    return max(keep)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    prices = [next(data) for _ in range(n)]
    print(n - best_keep(prices))


if __name__ == "__main__":
    solve()
