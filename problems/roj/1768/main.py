#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 01:10
# update_at: 2026-10-08 01:10

import sys
from functools import cache
from math import comb

MOD = 10 ** 9 + 7  # 答案取模的模数


@cache
def count(l: int, r: int, head: int, target: tuple[int, ...]) -> int:
    """区间 [l, r] 内的边各用一次、把恒等排列 [l..r] 变成目标排列的方案数。

    q 是 {0..n-2} 的全排列，每条相邻边恰好被用一次，任何数只能单向平移。
    倒过来看区间内最后一条被使用的边 k（交换位置 k, k+1）：交换后左块 [l..k] 的数
    再也去不了右块，所以交换前必须已把 {l..k} 凑在左侧；余下 r-l-1 条边里左块占
    k-l 条、右块占 r-k-1 条，两段可任意交错，系数 C(r-l-1, k-l)，两侧独立递归。
    head 是本区间最左位置上的值；合法子问题的内部位置 j 上的值恒等于 target[j]，
    右端点上的值就是区间内没出现过的那个数。
    """
    if l == r:
        return 1 if head == l else 0        # 区间只剩一个位置，内容必须正好是它自己
    if not l <= head <= r:
        return 0                            # 最左位置上的值不属于本区间，该子问题不可达
    used = 1 << head                        # 位掩码记录区间内已出现的值
    for j in range(l + 1, r):
        v = target[j]
        mismatch = not l <= v <= r or used >> v & 1
        if mismatch:
            return 0                        # 区间内容不成形状，该子问题不可达
        used |= 1 << v
    rest = ((1 << (r - l + 1)) - 1) << l & ~used
    if rest == 0:
        return 0
    tail = rest.bit_length() - 1            # 右端点上的值 = 区间内剩下的那个数
    content = (head,) + target[l + 1:r] + (tail,)   # 下标 i-l 对应位置 i

    total = 0
    low, high = 1 << 60, -(1 << 60)         # content 前缀极值；前缀为空时两个约束自动成立
    for ko in range(r - l):                 # ko = k - l，最后一条边是 (k, k+1)
        k = l + ko
        in_left = low >= l and high <= k and l <= content[ko + 1] <= k
        if in_left:
            # 交换位置 k,k+1 后左侧恰好是 {l..k}，两侧独立，再按 C(r-l-1, ko) 交错归并
            left_head = content[1] if ko == 0 else content[0]
            total += comb(r - l - 1, ko) * count(l, k, left_head, target) \
                * count(k + 1, r, content[ko], target)
        v = content[ko]
        low, high = min(low, v), max(high, v)
    return total % MOD


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)                          # 排列长度
    p = tuple(next(data) for _ in range(n))  # 目标排列

    print(count(0, n - 1, p[0], p) % MOD)


if __name__ == "__main__":
    solve()
