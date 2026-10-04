#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 21:18
# update_at: 2026-09-30 21:18

import sys
from collections import deque


def feasible(limit: int, cost: list[int], budget: int) -> bool:
    """是否存在抄题方案，使每段连续空题长度 ≤ limit 且总时间 ≤ budget。"""
    n = len(cost)
    if limit >= n:  # 一题都不抄：整段空题长度正好是 n
        return True

    # dp[i]：第 i 题抄、且前 i 题的空题段都不超过 limit 时的最小总时间；dp[0] = 0 表示一题未抄。
    # 第 i 题与上一道抄的题 j 之间空了 i-j-1 题，要求 i-j-1 ≤ limit，即 j ≥ i-limit-1。
    dp = [0] * (n + 1)
    window = deque([0])  # 单调队列存下标，队首恒为窗口 [i-limit-1, i-1] 内 dp 最小的 j
    for i in range(1, n + 1):
        while window[0] < i - limit - 1:  # 队首滑出窗口
            window.popleft()
        dp[i] = cost[i - 1] + dp[window[0]]
        while dp[window[-1]] >= dp[i]:  # 维护队内 dp 单调递增
            window.pop()
        window.append(i)

    # 末尾空段 n-i 也要 ≤ limit，所以最后一道抄的题 i 只需在 [n-limit, n] 里挑。
    return min(dp[n - limit:]) <= budget


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, budget = next(data), next(data)
    cost = [next(data) for _ in range(n)]

    # 空题段越长越安全（可行域对 limit 单调），二分最小可行 limit。
    lo, hi = 0, n
    while lo < hi:
        mid = (lo + hi) // 2
        if feasible(mid, cost, budget):
            hi = mid
        else:
            lo = mid + 1
    print(lo)


if __name__ == "__main__":
    solve()
