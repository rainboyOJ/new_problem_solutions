#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 20:14
# update_at: 2026-10-08 20:14

import sys
from bisect import bisect_left

MOD = 10 ** 9 + 7
INV2 = 500000004  # 2 在模 1e9+7 下的逆元，给等差数列求和公式用
LIMIT = 10 ** 9   # 题面 N 的上限；last(K) 首次 >= 1e9 时 K ≈ 4.4e5


def build_ends(limit: int) -> list[int]:
    """构造块右端点 ends：ends[v] = last(v) = 序列中 <= v 的项数；同时返回出现次数 a。

    序列自描述：值 v 的出现次数 a[v] 就是 Golomb 序列第 v 项，满足
    a[1]=1, a[2]=2, a[n+1] = 1 + a[n+1-a[a[n]]]。
    """
    a = [0, 1, 2]
    ends = [0, 1, 3]
    while ends[-1] < limit:
        a.append(1 + a[len(a) - a[a[-1]]])
        ends.append(ends[-1] + a[-1])
    return ends


def build_pref(ends: list[int]) -> list[int]:
    """pref[k] = 前 k 块对答案的完整贡献（第 i 块 = 块号 i × 块内位置编号之和）。"""
    pref = [0] * len(ends)
    for k in range(1, len(ends)):
        left, right = ends[k - 1] + 1, ends[k]
        # 位置编号之和用等差数列：块 k 覆盖 (ends[k-1], ends[k]]，值恒为 k
        pref[k] = (pref[k - 1] + k * (left + right) * (right - left + 1) * INV2) % MOD
    return pref


def last_last(n: int, ends: list[int], pref: list[int]) -> int:
    """求 last(last(n)) mod MOD：定位 n 所在块 g，整块查前缀和 + 末块等差部分。"""
    g = bisect_left(ends, n)  # 最小的 g 使 ends[g] >= n，即 n 所在块号
    left = ends[g - 1] + 1
    return (pref[g - 1] + g * (left + n) * (n - left + 1) * INV2) % MOD


def solve() -> None:
    ends = build_ends(LIMIT)
    pref = build_pref(ends)
    data = iter(map(int, sys.stdin.buffer.read().split()))
    T = next(data)
    print("\n".join(str(last_last(next(data), ends, pref)) for _ in range(T)))


if __name__ == "__main__":
    solve()
