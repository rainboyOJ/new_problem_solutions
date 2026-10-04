#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 04:41
# update_at: 2026-09-30 04:45

import sys

MASK = (1 << 64) - 1
HALF = 1 << 63


def to_ll(x: int) -> int:
    """把整数截成 64 位有符号 long long，与 std.cpp 溢出行为一致。"""
    x &= MASK
    return x - (1 << 64) if x >= HALF else x


def stirling2(n: int, k: int) -> int:
    """第二类 Stirling 数 S(n,k)：n 个不同元素划分成 k 个非空无标号集合的方案数。"""
    if k == 0 or k > n:
        return 0

    dp = [0] * (k + 2)
    dp[1] = 1  # S(1, 1) = 1

    for i in range(2, n + 1):
        upper = min(i, k)
        # 从大到小更新，避免覆盖上一行的状态。
        for j in range(upper, 0, -1):
            single = 1 if j == i else dp[j - 1]        # 第 i 个元素单独成一盒
            new_alone = 1 if j == 1 else dp[j]         # 第 i 个元素放进已有的某一盒
            dp[j] = to_ll(single + to_ll(j * new_alone))

    return dp[k]


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    n, k = int(data[0]), int(data[1])
    print(stirling2(n, k))


if __name__ == "__main__":
    solve()
