#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 22:10
# update_at: 2026-07-05 22:10

import sys
from itertools import accumulate


def feasible(scaled: list[int], x: int, L: int) -> bool:
    """判断是否存在长度 ≥ L 的子段，其平均值 ×1000 ≥ x。

    等价于：存在 i ≥ j + L 使 sum(scaled[j+1..i]) - x*(i-j) ≥ 0。
    令 b[k] = scaled[k] - x，只要 i-L 前缀位置的最小 b 前缀和 ≤ 当前前缀和。
    """
    prefix = list(accumulate((v - x for v in scaled), initial=0))  # b 的前缀和
    best = 0                       # 前 i-L 个前缀和的最小值（下标 0..i-L）
    for i in range(L, len(scaled) + 1):
        if prefix[i - L] < best:
            best = prefix[i - L]   # 滑动更新可用起点的最小前缀和
        if prefix[i] - best >= 0:  # 找到一个平均值不小于 x 的子段
            return True
    return False


def solve() -> None:
    data = map(int, sys.stdin.buffer.read().split())
    n, L = next(data), next(data)
    scaled = [next(data) * 1000 for _ in range(n)]  # 先放大 1000 倍，二分全程用整数

    # 二分最大的 x，使存在长度 ≥ L 的子段平均值 ×1000 ≥ x；答案就是最大 x。
    lo, hi = 0, max(scaled)
    while lo < hi:
        mid = (lo + hi + 1) // 2
        if feasible(scaled, mid, L):
            lo = mid
        else:
            hi = mid - 1
    print(lo)


if __name__ == "__main__":
    solve()
