#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 20:52
# update_at: 2026-09-30 20:52

import sys
from collections import deque

NEG = -10**12  # 前缀和绝对值不超过 2e8，哨兵足够小即可


def max_window_sum(pres: list[int], m: int) -> int:
    """长度不超过 m 的最大子段和：max(pres[i] - pres[j])，j ∈ [i-m, i-1]。"""
    dq: deque[int] = deque([0])  # 下标递增、前缀和递增；队首是当前最优左端点候选
    best = NEG
    for i in range(1, len(pres)):
        # 此刻队列只装下标 0..i-1，且队尾是 i-1（m >= 1），弹出后必不为空
        while dq[0] < i - m:  # 左端点滑出长度 m 的窗口
            dq.popleft()
        best = max(best, pres[i] - pres[dq[0]])  # 以 i 结尾、长度不超过 m 的最大和
        while dq and pres[dq[-1]] >= pres[i]:  # 维持递增：更小的前缀和对后面更有利（队列可能被清空）
            dq.pop()
        dq.append(i)
    return best


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    pres = [0]  # 前缀和：pres[i] = A_1..A_i 之和，pres[0] = 0
    for _ in range(n):
        pres.append(pres[-1] + next(data))
    print(max_window_sum(pres, m))


if __name__ == "__main__":
    solve()
