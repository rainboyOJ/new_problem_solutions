#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 08:13
# update_at: 2026-10-02 08:13

import sys
from collections import deque

NEG = -10**9  # dp 候选初值：净收益下界远大于此


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m, p = next(data), next(data), next(data)

    # coin[i][t]：第 i 条马路在第 t 个单位时间出现的金币（t 从 1 起）
    coin = [[0] + [next(data) for _ in range(m)] for _ in range(n)]  # n 行 × m 列
    cost = [next(data) for _ in range(n)]  # 每个工厂买机器人的花费

    # 对角线 c：时刻 t 经过的马路是 (t + c - 1) % n，一次行程恰好沿一条对角线前进。
    # prefix[c] 滚动维护该对角线的前缀和；队列里存 (k, dp[k] - 前缀和 - 购买花费)。
    prefix = [0] * n
    queues = [deque() for _ in range(n)]  # 每条对角线一个单调队列，窗口最大值 O(1)
    dp = [0] * (m + 1)  # dp[j]：前 j 个单位时间能拿到的最大净收益

    for j in range(1, m + 1):
        best = NEG
        for c in range(n):
            k = j - 1  # 上一段恰好覆盖前 k 个单位时间，本段从 k+1 时刻起步
            # 此刻 prefix[c] 正是 P_c[k]；起步工厂即 (k+1) 时刻所在的工厂
            value = dp[k] - prefix[c] - cost[(k + c) % n]
            q = queues[c]
            while q and q[-1][1] <= value:
                q.pop()  # 队尾收益不比新值大，之后永远轮不到它
            q.append((k, value))
            while q[0][0] < j - p:  # 机器人最多走 p 步，本段长度 j-k ≤ p
                q.popleft()
            prefix[c] += coin[(j + c - 1) % n][j]  # 前缀和推进到时刻 j
            best = max(best, prefix[c] + q[0][1])
        dp[j] = best

    print(dp[m])


if __name__ == "__main__":
    solve()
