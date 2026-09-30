#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 21:10
# update_at: 2026-09-30 21:10

import sys
from collections import deque

INF = 1 << 60  # 不可达状态的初值：比任何合法代价都大，用作单调队列的初始地板


def min_cost(n: int, m: int, cost: list[int]) -> int:
    """在前 n 座烽火台上选出「任意连续 m 座至少选一座」的最小总代价。

    记 dp[i] 为「第 i 座必须点火，且前缀 [1, i] 已经满足约束」的最小代价。
    i 与 i-1 之间最多隔 m-1 座不点，所以上一个点火位置落在 [i-m, i-1]，
    于是 dp[i] = a[i] + min(dp[i-m .. i-1])：滑动窗口取最小值，用单调队列做到均摊 O(1)。
    """
    # 位置 0 是虚拟哨兵：滑到 i = 1 时它正好离开窗口，代表「前面一段没点火也不越界」。
    dp = [INF] * (n + 1)
    dp[0] = 0
    window = deque([0])  # 存下标，对应 dp 值自队首到队尾单调不减

    for i in range(1, n + 1):
        while window[0] < i - m:  # 队首滑出左界 i-m，不再能作为转移来源
            window.popleft()
        dp[i] = dp[window[0]] + cost[i - 1]
        while window and dp[window[-1]] >= dp[i]:  # 更晚进队却更优，旧的下标永远没用
            window.pop()
        window.append(i)

    # 尾部没有强制点火的烽火台：最后一座点火的 j 只要满足 n - j <= m-1，
    # 即 j >= n-m+1，剩下的 j+1..n 就都不超过 m-1 座，同样合法。
    # 下界再和 1 取大：m > n 时整条链不足 m 座，答案退化为「选最便宜的一座」，
    # 否则会把哨兵 dp[0]=0 当成合法结尾，误输出 0。
    while window[0] < max(1, n - m + 1):
        window.popleft()
    return dp[window[0]]


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    n, m = data[0], data[1]
    cost = data[2:2 + n]
    print(min_cost(n, m, cost))


if __name__ == "__main__":
    solve()
