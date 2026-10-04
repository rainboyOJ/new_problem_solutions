#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 04:18
# update_at: 2026-09-30 04:18

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    a = [next(data) for _ in range(n)]

    # 离散化：车厢号两两不同，排名即在排序后序列中的位置，压到 1..n 方便树状数组下标
    rank = {v: i for i, v in enumerate(sorted(a), 1)}

    tree = [0] * (n + 1)  # 树状数组：维护"已出现元素"按排名的计数
    inversions = 0        # 逆序对总数 = 最少旋转次数
    seen = 0              # 已扫过的元素个数

    for x in a:
        i = rank[x]

        # 前缀和：排名 <= i 的已出现元素个数
        prefix = 0
        j = i
        while j:
            prefix += tree[j]
            j -= j & -j
        # 比 x 大的已出现元素 = 它们与 x 各构成一个逆序对
        inversions += seen - prefix

        j = i              # 把 x 计入树状数组
        while j <= n:
            tree[j] += 1
            j += j & -j
        seen += 1

    print(inversions)


if __name__ == "__main__":
    solve()
