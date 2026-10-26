#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-26 13:36
# update_at: 2026-10-26 13:36

import sys

NEG = -10**18  # 负无穷哨兵: 表示 dp 状态不可达


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    f = next(data)  # 花束数
    v = next(data)  # 花瓶数
    # a[i][j]: 花束 i 放入花瓶 j 的美学值, 下标从 1 开始.
    a = [[0] * (v + 1)] + [[0] + [next(data) for _ in range(v)] for _ in range(f)]

    # dp[i][j]: 前 i 束花放入前 j 个花瓶(每瓶至多一束)的最大美学值.
    dp = [[NEG] * (v + 1) for _ in range(f + 1)]
    dp[0] = [0] * (v + 1)
    for i in range(1, f + 1):
        for j in range(i, v + 1):
            dp[i][j] = max(dp[i][j - 1], dp[i - 1][j - 1] + a[i][j])

    # 从 (f, v) 反推方案: 不取花瓶 j 就左移, 否则花束 i 放花瓶 j, 向左上走.
    plan: list[int] = []
    i, j = f, v
    while i > 0:
        if j > i and dp[i][j] == dp[i][j - 1]:
            j -= 1
        else:
            plan.append(j)
            i -= 1
            j -= 1

    print(dp[f][v])
    print(" ".join(map(str, plan[::-1])))


if __name__ == "__main__":
    solve()
