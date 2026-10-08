#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 20:04
# update_at: 2026-10-08 20:04

import sys

# 每人做软件 1、软件 2 一个模块分别需要的天数
type Techs = list[tuple[int, int]]


def feasible(days: int, m: int, tech: Techs) -> bool:
    """判定 days 天内能否把两个软件各 m 个模块都做完。

    同一时刻一个人只做一个模块，所以按人切时间片：第 i 人先做 k 个软件 1 的
    模块、余下天数全做软件 2。dp[j] 表示软件 1 排到 j 个模块时软件 2 最多能做
    多少（-1 表示该状态排不出）；软件 1 多做无益，j + k 超过 m 一律截断到 m。
    """
    dp = [-1] * (m + 1)  # dp[j]：软件 1 已完成 j 个模块时，软件 2 最多完成的模块数
    dp[0] = 0

    for d1, d2 in tech:
        kmax = min(m, days // d1)  # 这个人最多能承担多少个软件 1 的模块
        ndp = [-1] * (m + 1)
        for j, done2 in enumerate(dp):
            if done2 < 0:
                continue
            for k in range(kmax + 1):
                nxt_j = min(m, j + k)  # 超过 m 的软件 1 模块无意义，归到 m
                ndp[nxt_j] = max(ndp[nxt_j], done2 + (days - k * d1) // d2)
        dp = ndp

    return dp[m] >= m


def min_days(m: int, tech: Techs) -> int:
    """二分两个软件都交付的最少天数。

    天数单调：D 天能完成则 D+1 天也能。上界取「某一人独自做完两个软件全部
    2m 个模块」，需 m*(d1+d2) <= 2*m*max_d 天，该值必然可行。
    """
    lo, hi = 0, 2 * m * max(max(pair) for pair in tech)
    while lo < hi:
        mid = (lo + hi) // 2
        if feasible(mid, m, tech):
            hi = mid
        else:
            lo = mid + 1
    return lo


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    tech: Techs = [(next(data), next(data)) for _ in range(n)]
    print(min_days(m, tech))


if __name__ == "__main__":
    solve()
