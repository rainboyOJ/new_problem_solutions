#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 16:47
# update_at: 2026-10-02 16:47

import sys


def divisor_count_sum(n: int) -> int:
    """S(n) = 1..n 每个数的约数个数之和：按商 floor(n/l) 分块累加。

    d(k) = ∑_{d|k} 1，交换求和顺序后 S(n) = ∑_{d=1}^{n} floor(n/d)；
    商 floor(n/l) 只有 O(√n) 种取值，同一商的 l 是连续区间 [l, r]。
    """
    total = 0
    l = 1
    while l <= n:
        q = n // l        # 当前块的商
        r = n // q        # 商仍为 q 的最大左端点
        total += q * (r - l + 1)
        l = r + 1
    return total


def solve() -> None:
    t1, t2 = map(int, sys.stdin.buffer.read().split())
    print(divisor_count_sum(t2) - divisor_count_sum(t1 - 1))


if __name__ == "__main__":
    solve()
