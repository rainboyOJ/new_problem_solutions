#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 20:51
# update_at: 2026-10-07 21:00

import sys


def count_132(perm: list[int]) -> int:
    """统计 i<j<k 且 a[i]<a[k]<a[j] 的三元组个数（经典 132 计数）。"""
    n = len(perm)
    bit = [0] * (n + 1)  # 树状数组，下标是名次，记录已扫过的位置里每个名次出现了几次
    ans = 0
    for j, value in enumerate(perm, 1):
        pre = 0  # 左侧比 value 小的个数 = 名次 <= value-1 的前缀和
        x = value - 1
        while x > 0:
            pre += bit[x]
            x -= x & -x
        # 比 value 小的数共 value-1 个，其中 pre 个在左侧，其余都在右侧；
        # 右侧元素共 n-j 个，减掉右侧比它小的，就是右侧比它大的个数 last。
        last = (n - j) - (value - 1 - pre)
        # 以 value 为最小元素、右侧任取两个更大元素共 C(last,2) 个三元组，
        # 其中 123 型（value<a[k]<a[l]）有 pre*last 个，相减剩下的就是 132 型。
        ans += last * (last - 1) // 2 - pre * last
        x = value  # 把 value 的名次插入树状数组
        while x <= n:
            bit[x] += 1
            x += x & -x
    return ans


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)  # 羊的总数
    raw = [next(data) for _ in range(n)]
    # 题面【提示】保证是 1..N 的排列，这里仍做一次离散化：名次 rank 满足
    # rank-1 恰好是"比它小的数的个数"，且下标恒落在 1..n 内。
    rank = {value: i for i, value in enumerate(sorted(raw), 1)}
    print(count_132([rank[value] for value in raw]))


if __name__ == "__main__":
    solve()
