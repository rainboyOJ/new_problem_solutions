#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-11-04 11:40
# update_at: 2026-11-04 11:40

import sys
from collections.abc import Iterable
from itertools import accumulate

type Dif = list[int]   # dif[i] = 第 i 位对"偶数位和"的贡献变化：奇数下标 +a[i]，偶数下标 -a[i]


def max_segment(values: Iterable[int]) -> int:
    """最大子段和，允许空段（返回 >= 0）；等价于 Kadane 的 f[i] = max(f[i-1]+v, v)。"""
    return max(accumulate(values, lambda acc, v: max(acc + v, v)), default=0)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    T = next(data)
    out: list[str] = []

    for _ in range(T):
        n = next(data)
        a = [next(data) for _ in range(n)]

        # 反转偶数长度区间 [l, r] 后，区间内奇数下标的元素被搬到偶数位、偶数下标的被搬走：
        # 收益 = 区间奇数下标之和 - 偶数下标之和，也就是 dif 上的一个子段和。
        dif: Dif = [a[i] if i & 1 else -a[i] for i in range(n)]

        # 偶数长度 ⇒ l 与 r 奇偶不同，于是合法区间只有两类，各自对应 dif 的相邻对：
        #   l 偶下标 → 对是 (0,1), (2,3), ...；l 奇下标 → 对是 (1,2), (3,4), ...
        # 两类各自合并成"对的序列"再取最大子段和，zip 会自动截断，不用管 n 的奇偶。
        even_start = [x + y for x, y in zip(dif[0::2], dif[1::2])]
        odd_start = [x + y for x, y in zip(dif[1::2], dif[2::2])]

        gain = max(0, max_segment(even_start), max_segment(odd_start))  # 0 = 不反转
        out.append(sum(a[0::2]) + gain)

    print('\n'.join(map(str, out)))


if __name__ == "__main__":
    solve()
