#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 20:53
# update_at: 2026-09-30 20:53

import sys
from collections import deque


def max_efficiency(effs: list[int], k: int) -> int:
    """前缀和 + 单调队列求「不选超过 k 只连续奶牛」的最大效率和。

    dp[i] = max(dp[i-1], S[i] + max_{i-k <= j <= i-1} (dp[j-1] - S[j]))，
    其中 j 是连续段左侧第一只不选的奶牛（j = 0 表示从头开始选），
    窗口最大值由下标递增、候选值递减的双端队列维护。
    """
    # (下标 j, 候选值 dp[j-1]-S[j])，队首最大；j=0 的候选值是 0 - S[0] = 0
    window: deque[tuple[int, int]] = deque([(0, 0)])
    prefix = 0      # S[i]：前 i 只奶牛的效率和
    dp_prev = 0     # dp[i-1]：前 i-1 只奶牛的答案

    for i, eff in enumerate(effs, 1):
        prefix += eff                                  # S[i] = S[i-1] + E_i
        if window and window[0][0] < i - k:            # 窗口左端 [i-k, i-1] 过期一个下标
            window.popleft()
        # 只有 k = 0 时窗口为空（一只都不许选），其余情况 dp[i-1] 必在候选里
        dp_cur = prefix + window[0][1] if window else dp_prev
        dp_cur = max(dp_cur, dp_prev)                  # 第 i 只不选，直接继承

        # 入队候选 j = i：值为 dp[i-1] - S[i]（奶牛 i 不选时，前缀最优值）
        # 保持候选值递减，过期下标靠左端弹出，均摊 O(1)
        value = dp_prev - prefix
        while window and window[-1][1] <= value:
            window.pop()
        window.append((i, value))
        dp_prev = dp_cur

    return dp_prev


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, k = next(data), next(data)
    effs = [next(data) for _ in range(n)]
    print(max_efficiency(effs, k))


if __name__ == "__main__":
    solve()
