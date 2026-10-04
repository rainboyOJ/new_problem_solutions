#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 11:16
# update_at: 2026-10-01 11:16

import sys
from collections import deque
from itertools import accumulate


def max_subsum_within(pre: list[int], m: int) -> int:
    """长度不超过 m 的连续子段的最大和：枚举右端点 j，单调队列给出 [j-m, j-1] 内的最小前缀和。"""
    queue: deque[int] = deque([0])  # 存前缀和下标，队头到队尾的值严格递增，队头即窗口内最小值
    best = pre[1] - pre[0]          # 子段长度至少为 1，先用第一个数兜底
    for j in range(1, len(pre)):
        while queue[0] < j - m:     # 队头下标太老，对应子段长度超过 m
            queue.popleft()
        best = max(best, pre[j] - pre[queue[0]])
        while queue and pre[queue[-1]] >= pre[j]:  # 不比 pre[j] 小的下标永远当不了后面的最小值
            queue.pop()
        queue.append(j)
    return best


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    m = next(data)
    nums = [next(data) for _ in range(n)]

    pre = [0, *accumulate(nums)]  # 前缀和：pre[j] - pre[i] 即子段 a[i+1..j] 的和
    print(max_subsum_within(pre, m))


if __name__ == "__main__":
    solve()
