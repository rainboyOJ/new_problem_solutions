#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 10:29
# update_at: 2026-10-02 10:29

import sys

MOD = 99_999_997  # 题面取模数：99,999,997


def rank_of(values: list[int]) -> dict[int, int]:
    """把一列高度映射成排名：最小的为 1（同列高度互不相同，无并列）。"""
    return {value: rank for rank, value in enumerate(sorted(values), 1)}


def count_inversions(order: list[int]) -> int:
    """树状数组统计逆序对数：依次插入各值，用"已插入个数 - 前缀和"得到比它大的个数。

    逆序对数 = 把 order 变为升序所需的最少相邻交换次数。
    """
    size = len(order)
    tree = [0] * (size + 1)
    inversions = 0

    for seen, value in enumerate(order, 1):
        le = 0  # 已插入中小于等于 value 的个数
        j = value
        while j:
            le += tree[j]
            j -= j & -j
        inversions += seen - 1 - le  # 已插入的比 value 大的个数

        j = value
        while j <= size:
            tree[j] += 1
            j += j & -j

    return inversions


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    a = [next(data) for _ in range(n)]
    b = [next(data) for _ in range(n)]

    # 最小距离 ⇔ 两列按排名同位配对（排序不等式）；距离只取决于配对关系，
    # 所以把第 1 列原样当作目标排列，只重排第 2 列，总次数即两排列的 Kendall 距离。
    rank_of_a = rank_of(a)
    rank_of_b = rank_of(b)

    # 第 2 列第 i 根要与第 1 列同排名的那根同位，记下它在第 1 列中的位置
    pos_of_rank: dict[int, int] = {}
    for pos, value in enumerate(a):
        pos_of_rank[rank_of_a[value]] = pos
    order = [pos_of_rank[rank_of_b[value]] for value in b]

    # 下标从 0 起，平移成 1 起以适配树状数组
    print(count_inversions([pos + 1 for pos in order]) % MOD)


if __name__ == "__main__":
    solve()
