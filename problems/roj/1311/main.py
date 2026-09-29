#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 04:29
# update_at: 2026-09-30 04:29

import sys


def inversions(values: list[int]) -> int:
    """求逆序对总数：离散化后从左往右扫，用树状数组统计「前面比它大」的个数。

    逆序对只关心相对大小，所以先把每个值换成它在全体不同值中的名次（离散化），
    值域从 1e5 压到至多 n，树状数组的下标才开得下。扫到 x 时，树状数组里装的
    正是它左边的所有数：前缀和给出其中「值 ≤ x」的个数，用已插入个数减掉它，
    剩下的每一个都比 x 大，各自与 x 组成一个逆序对。
    """
    n = len(values)
    rank = {v: i for i, v in enumerate(sorted(set(values)), 1)}  # 值 -> 名次 1..n
    bit = [0] * (n + 1)          # 树状数组：名次 i 已经出现过几次
    total = 0
    for seen, x in enumerate(values):
        i = rank[x]

        prefix = 0               # 已插入元素中名次 ≤ i（即值 ≤ x）的个数
        j = i
        while j:
            prefix += bit[j]
            j -= j & -j
        total += seen - prefix   # 左边比 x 大的那些，各与 x 构成一个逆序对

        j = i                    # 把 x 登记进树状数组
        while j <= n:
            bit[j] += 1
            j += j & -j
    return total


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    values = [next(data) for _ in range(n)]
    print(inversions(values))


if __name__ == "__main__":
    solve()
