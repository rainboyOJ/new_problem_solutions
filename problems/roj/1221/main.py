#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 00:30
# update_at: 2026-09-30 00:37

import sys
from functools import cache
from math import gcd

FULL = 0  # 空集合的位掩码，单独命名避免裸写 0 引起歧义


def conflict_mask(value: int, others: list[int]) -> int:
    """与 value 不互质的那些数在 others 里的下标位：这些数不能和它同组。"""
    return sum(1 << j for j, other in enumerate(others) if gcd(value, other) > 1)


def subsets_desc(mask: int) -> list[int]:
    """降序列出 mask 的全部非空子集（标准 t = (t-1) & mask 技巧）。"""
    result: list[int] = []
    t = mask
    while t:
        result.append(t)
        t = (t - 1) & mask
    return result


def min_groups(n: int, values: list[int]) -> int:
    """把 n 个数分成最少的组，使每组内任意两数互质（等价于冲突图的最少染色数）。

    冲突图：i -- j 当且仅当 gcd(a_i, a_j) > 1。组内两两互质就是独立集，
    所以答案 = 覆盖全部点的最少独立集个数 = 冲突图的最小染色数。
    按子集 DP：f[S] = 1 + min{ f[S \\ T] : T ⊆ S 且 T 是独立集 }。
    """
    # full[i]：与 a_i 冲突（gcd > 1）的下标位，用来快速判定"能否同组"
    full = [conflict_mask(values[i], values) for i in range(n)]

    # independent[S]：S 内部两两互质。去掉最低位 v 的点后，只需 v 与剩余部分都不冲突
    independent = bytearray(1 << n)
    independent[FULL] = 1
    for s in range(1, 1 << n):
        low = s & -s
        v = low.bit_length() - 1
        rest = s ^ low
        independent[s] = independent[rest] and not (full[v] & rest)

    # 每个集合的独立子集表：只枚举一次，DP 里直接查表
    ind_subsets = [subsets_desc(s) for s in range(1 << n)]

    @cache
    def best(s: int) -> int:
        """覆盖集合 s 所需的最少组数。"""
        if s == FULL:
            return 0
        low = s & -s  # 最优划分中必有一组包含 s 的最低位的点，只需枚举含它的独立集
        return 1 + min(
            best(s ^ t) for t in ind_subsets[s] if t & low and independent[t]
        )

    return best((1 << n) - 1)


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    n = data[0]
    values = data[1:1 + n]
    print(min_groups(n, values))


if __name__ == "__main__":
    solve()
