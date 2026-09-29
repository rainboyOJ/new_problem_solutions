#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 01:08
# update_at: 2026-09-30 01:17

import sys


def inversions(perm: list[int]) -> int:
    """求排列（互不相同的数）的逆序数：树状数组统计每个元素前面比它大的个数。

    逆序对只关心相对大小，所以先把值域压成排名 1..n。从左往右扫，
    树状数组的前缀和给出「已经插入的元素里排名不超过当前值」的个数，
    用已插入总数减去它就是新产生的逆序对数。
    """
    n = len(perm)
    rank = {v: i for i, v in enumerate(sorted(perm), 1)}  # 值域 1e8 → 排名 1..n
    bit = [0] * (n + 1)                                  # 下标即排名，1 表示该排名已出现
    ans = 0
    for seen, v in enumerate(perm):
        i = rank[v]
        less = 0                # 已插入元素中排名 ≤ i（即值 ≤ v）的个数
        j = i
        while j:
            less += bit[j]
            j -= j & -j
        ans += seen - less      # 前面 seen 个里比 v 大的都是逆序
        j = i
        while j <= n:
            bit[j] += 1
            j += j & -j
    return ans


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    n = int(data[0])                        # 排列长度
    perm = list(map(int, data[1:1 + n]))
    print(inversions(perm))


if __name__ == "__main__":
    solve()
