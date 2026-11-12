#!/usr/bin/env python3
"""Codeforces 1061C Multiplicity - 暴力子集枚举 Pythonic 实现。

核心思路：
1. 原数组长度为 n，优秀子序列的长度 k 可以为 1, 2, ..., n；
2. 利用 itertools.combinations(a, k) 保序枚举所有长度为 k 的子序列；
3. 利用 all(val % i == 0 for i, val in enumerate(sub, 1)) 校验 1-based 下标的整除条件；
4. 利用 sum 生成器表达式完成无冗余统计。
"""
from itertools import combinations
import sys


def solve() -> None:
    lines = sys.stdin.read().split()
    if not lines:
        return
    n = int(lines[0])
    a = [int(x) for x in lines[1:]]

    MOD = 1_000_000_007

    # 枚举所有非空长度 k，对每个子序列校验其优秀性
    ans = sum(
        all(val % i == 0 for i, val in enumerate(sub, 1))
        for k in range(1, n + 1)
        for sub in combinations(a, k)
    ) % MOD

    print(ans)


if __name__ == "__main__":
    solve()
