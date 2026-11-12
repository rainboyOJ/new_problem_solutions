#!/usr/bin/env python3
"""Codeforces 1829H Don't Blame Me - 暴力子集枚举实现。

核心逻辑：
1. 原数组长度为 n，任意非空子序列即为原数组的非空子集（长度 m 从 1 到 n）；
2. 使用 itertools.combinations(a, m) 保序枚举所有子序列；
3. 使用 functools.reduce(operator.and_, sub) 累积计算子序列所有元素的按位与（AND）结果；
4. 使用内置方法 val.bit_count() 统计结果中二进制 1 的个数是否恰好等于 k；
5. 累加所有满足条件的子集数量，对 10^9 + 7 取模。
"""
from functools import reduce
from itertools import combinations
import operator
import sys


def solve() -> None:
    lines = sys.stdin.read().split()
    if not lines:
        return
    it = iter(lines)

    t = int(next(it))
    MOD = 1_000_000_007
    out = []

    for _ in range(t):
        n = int(next(it))
        k = int(next(it))
        a = [int(next(it)) for _ in range(n)]

        # 枚举所有非空长度 m，对每个子集执行 reduce(AND) 并检查 bit_count() == k
        ans = sum(
            reduce(operator.and_, sub).bit_count() == k
            for m in range(1, n + 1)
            for sub in combinations(a, m)
        ) % MOD

        out.append(str(ans))

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
