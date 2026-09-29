#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 04:10
# update_at: 2026-09-30 04:10

import sys
from itertools import accumulate


def max_two_segments(a: list[int]) -> int:
    """求两个不重合连续子段之和的最大值（子段不交，且各至少一个元素）。"""
    # f[i]：右端点恰为 i 的最大子段和 —— 要么单取 a[i]，要么接在 f[i-1] 后面
    f = list(accumulate(a, lambda best, x: max(x, best + x)))

    # g[i]：在 a[0..i] 里任取一段的最大子段和，即前缀最大值
    g = list(accumulate(f, max))

    # h[i]：左端点恰为 i 的最大子段和，反向递推
    h = list(accumulate(reversed(a), lambda best, x: max(x, best + x)))
    h.reverse()

    # 枚举右段左端点 s，左段在 s 前面任取：ans = max(g[s-1] + h[s])
    return max(g[i] + h[i + 1] for i in range(len(a) - 1))


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)  # 测试组数

    for _ in range(T):
        n = next(data)
        a = [next(data) for _ in range(n)]  # 题面的 a_1..a_n
        out.append(str(max_two_segments(a)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
