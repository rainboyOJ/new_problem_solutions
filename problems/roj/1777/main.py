#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 01:55
# update_at: 2026-10-08 01:55

import sys
from math import comb

BITS = 64  # n 的二进制位数上界：题目要求输出的 n 落在 [1, 2^64 - 1]


def kth_number(rank: int, ones: int) -> int:
    """第 rank 小（rank 从 1 起）的「二进制恰有 ones 个 1」的非负整数。"""
    x = 0
    used = 0
    for i in range(BITS - 1, -1, -1):
        # 本位取 0 时，低位 i 位里还要凑出 need 个 1，方案数为 C(i, need)
        need = ones - used
        ways = comb(i, need) if 0 <= need <= i else 0
        if rank > ways:  # 目标不在「本位取 0」这一支里，本位必须取 1
            rank -= ways
            x |= 1 << i
            used += 1
        if used == ones:
            break  # 1 已放满，低位全填 0
    return x


def answer(m: int, k: int) -> tuple[int, int]:
    """f(n) = m 时的 (最小 n, 解的个数)；个数 -1 表示无穷多。

    恒等式 f(n) = #{ j < n : popcount(j) = k-1 } 把 n 的取值压成一段连续区间：
    m >= 1 时是 [a_{m-1}+1, a_m]（a_i 为第 i+1 个候选），m == 0 时是 [1, 2^(k-1)-1]。
    """
    if k == 1:
        return (1, -1) if m == 1 else (0, 0)  # 候选只有 j = 0，f 恒为 1
    p = k - 1
    if m == 0:
        return 1, (1 << p) - 1
    if comb(BITS, p) < m + 1:
        return 0, 0  # 2^64 内凑不出 m+1 个候选，题面保证不会出现
    low = kth_number(m, p)      # a_{m-1}
    high = kth_number(m + 1, p)  # a_m
    return low + 1, high - low


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    t = next(data)
    out: list[str] = []

    for _ in range(t):
        m, k = next(data), next(data)
        first, count = answer(m, k)
        out.append(f"{first} {count}")

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
