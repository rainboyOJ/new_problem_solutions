#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 20:22
# update_at: 2026-10-01 20:22

import sys

MOD = 1 << 31   # 题面模数 2147483648 = 2^31，不是常用的 1e9+7
MASK = MOD - 1  # 模数是 2 的幂，非负数下 & MASK 与 % MOD 等价，省掉内层的除法开销


def partitions(n: int) -> int:
    """把 n 无序拆成若干个正整数之和的方案数，加数可重复、至少两个。

    完全背包计数：加数 i 是体积为 i 且数量无限的物品，dp[j] 是和恰为 j 的方案数。
    """
    dp = [0] * (n + 1)
    dp[0] = 1                       # 空拆分：所有转移的起点

    # 外层 i = 本轮起允许使用的最大加数，答案按“最大加数”分层以避免顺序重复
    for i in range(1, n + 1):
        # 内层正序 → dp[j-i] 已含本轮结果，加数 i 可重复取，这是完全背包的标志
        for j in range(i, n + 1):
            dp[j] = (dp[j] + dp[j - i]) & MASK

    # dp[n] 里只有 1 个方案是单加数拆分 n = n，题面要求至少两个数，扣掉它
    return (dp[n] - 1) & MASK


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    print(partitions(n))


if __name__ == "__main__":
    solve()
