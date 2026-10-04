#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 16:50
# update_at: 2026-09-30 16:50

import sys
from itertools import accumulate


def prefix_sum(bit: list[int], i: int) -> int:
    """前缀和：累加 bit 中管辖 [1..i] 的 O(log n) 个结点。"""
    s = 0
    while i:
        s += bit[i]
        i -= i & -i  # lowbit：去掉最低位的 1，沿父链上跳
    return s


def add(bit: list[int], i: int, delta: int) -> None:
    """单点加：把 delta 累加到第 i 个元素，并更新所有管辖 i 的结点。"""
    while i < len(bit):
        bit[i] += delta
        i += i & -i  # lowbit：跳到把本段纳入区间的上层结点


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    values = [next(data) for _ in range(n)]

    # 树状数组建树：pre 是前缀和，bit[i] 恰为 (i-lowbit(i), i] 的区间和，一次推导式 O(n) 建好
    pre = list(accumulate(values, initial=0))
    bit = [0] + [pre[i] - pre[i - (i & -i)] for i in range(1, n + 1)]

    out: list[str] = []
    for _ in range(m):
        k, a, b = next(data), next(data), next(data)
        if k == 1:  # k=1：第 a 个数加 b
            add(bit, a, b)
        else:  # 其余 k 都是求子数列 [a,b] 的连续和（样例 k=0，真实数据 k=2）
            out.append(str(prefix_sum(bit, b) - prefix_sum(bit, a - 1)))
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
