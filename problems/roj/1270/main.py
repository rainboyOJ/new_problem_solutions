#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 02:38
# update_at: 2026-09-30 02:38

import sys


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    it = iter(data)
    m = next(it)          # 背包容量
    n = next(it)          # 物品数量
    dp = [0] * (m + 1)    # dp[j] 表示容量 j 能获得的最大价值

    for _ in range(n):
        w = next(it)      # 单件重量
        c = next(it)      # 单件价值
        p = next(it)      # 可取件数：0 表示无限

        if p == 0:
            # 完全背包：正序，让同一物品被重复选取
            for j in range(w, m + 1):
                dp[j] = max(dp[j], dp[j - w] + c)
        else:
            # 有限件时按二进制拆成若干 01 背包物品
            k = 1
            while k <= p:
                wt, ct = k * w, k * c
                for j in range(m, wt - 1, -1):
                    dp[j] = max(dp[j], dp[j - wt] + ct)
                p -= k
                k <<= 1
            if p:
                wt, ct = p * w, p * c
                for j in range(m, wt - 1, -1):
                    dp[j] = max(dp[j], dp[j - wt] + ct)

    print(dp[m])


if __name__ == "__main__":
    solve()
