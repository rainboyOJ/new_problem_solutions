#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 09:40
# update_at: 2026-10-02 09:40

import sys
from itertools import accumulate

MOD = 1000007  # 题面指定的模数（不是常见的 10^9+7）


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    caps: list[int] = [min(next(data), m) for _ in range(n)]  # 超过 m 的上限永远用不到

    # dp[x] = 摆 x 盆花的方案数；逐种花做「长度 cap+1 的滑动窗口和」
    dp = [0] * (m + 1)
    dp[0] = 1  # 一种花都不摆
    for cap in caps:
        pre = list(accumulate(dp, initial=0))  # pre[x] = 摆前若干盆的方案数前缀和
        # 新方案数 = 窗口 dp[x-cap..x] 的和 = pre[x+1] - pre[x-cap]（下标截到 0）
        dp = [(pre[x + 1] - pre[max(x - cap, 0)]) % MOD for x in range(m + 1)]

    print(dp[m])


if __name__ == "__main__":
    solve()
