#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 15:02
# update_at: 2026-10-08 15:02

import sys


def solve() -> None:
    """把序列划分成段和不下降的若干段，段数最多，答案 = N - 段数。"""
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    pre = [0] * (n + 1)  # pre[i]：前 i 座塔的高度和
    for i in range(1, n + 1):
        pre[i] = pre[i - 1] + next(data)

    dp = [0] * (n + 1)  # dp[i]：前 i 座塔合法划分时，最后一段和的最小值
    g = [0] * (n + 1)   # g[i]：取到 dp[i] 时的最多段数
    for i in range(1, n + 1):
        # 倒序枚举断点 j：A_i>=1 时前缀和严格递增，第一个满足 pre[i]-pre[j] >= dp[j]
        # 的 j 就给出最小的末段和（j=0 恒合法，转移必定存在）。
        for j in range(i - 1, -1, -1):
            if pre[i] - pre[j] >= dp[j]:
                dp[i] = pre[i] - pre[j]
                g[i] = g[j] + 1
                break

    print(n - g[n])


if __name__ == "__main__":
    solve()
