#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 03:55
# update_at: 2026-09-30 03:55

import sys


def suffix_best(prices: list[int]) -> list[int]:
    """suf[i]：只在第 i 天及以后做一次买入卖出能拿到的最大利润（同天买卖记 0）。"""
    n = len(prices)
    suf = [0] * n
    high = prices[-1]  # 第 i 天右侧见过的最高价，只能当卖出价
    best = 0           # 窗口 [i, n-1] 内一次买卖的最大利润，天然不小于 0
    for i in range(n - 2, -1, -1):
        best = max(best, high - prices[i])  # 第 i 天买入、右侧最高价卖出
        suf[i] = best
        high = max(high, prices[i])
    return suf


def max_two_trades(prices: list[int]) -> int:
    """两次买卖的最大总利润：第二次买入允许与第一次卖出在同一天。"""
    suf = suffix_best(prices)
    ans = 0
    low = prices[0]  # 前缀里见过的最低买入价
    gain = 0         # 前缀 [0, i] 内做一次买卖的最大利润，也天然不小于 0
    for i, p in enumerate(prices):
        low = min(low, p)
        gain = max(gain, p - low)
        # 第一次买卖整体落在 [0, i]，第二次落在 [i, n-1]：卖出日 <= i <= 买入日
        ans = max(ans, gain + suf[i])
    return ans


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)

    for _ in range(T):
        days = next(data)  # 天数 N
        prices = [next(data) for _ in range(days)]
        out.append(str(max_two_trades(prices)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
