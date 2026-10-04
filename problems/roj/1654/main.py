#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 00:18
# update_at: 2026-10-01 00:20

import sys
from itertools import accumulate

MOD = 100003  # 题面模数 10^5 + 3


def build_tables(limit: int) -> tuple[list[list[int]], list[list[int]]]:
    """建两张下三角表：pascal[n][r] = C(n, r)，falling[n][r] = P(n, r)。

    C(n, r) 用杨辉递推；P(n, r) = n(n-1)…(n-r+1) 是下降幂，
    用前缀积（accumulate）一次算完整行，不必对每个 r 重新乘一遍。
    表只需要前 limit+1 行——最大的下标来自 a+c、b、d、k，不超过 a+c 量级。
    """
    pascal: list[list[int]] = [[1]]
    for n in range(1, limit + 1):
        prev = pascal[-1]
        pascal.append([1] + [(prev[r - 1] + prev[r]) % MOD for r in range(1, n)] + [1])

    # 前缀积的序列是 1, n, n-1, …, 1，开头补的 1 让 falling[n][0] = 1。
    falling: list[list[int]] = [
        list(accumulate([1, *range(n, 0, -1)], lambda x, y: x * y % MOD))
        for n in range(limit + 1)
    ]
    return pascal, falling


def solve() -> None:
    a, b, c, d, k = map(int, sys.stdin.buffer.read().split())

    # 组合/排列的顶层下标只会是 b、a+c、d、k 之一，取最大者即为表的规模。
    pascal, falling = build_tables(max(b, a + c, d, k))

    def ways(rows: int, cols: int, used: int) -> int:
        """在 rows 行 × cols 列的矩形里放 used 个互不攻击的车的方案数。

        两步独立相乘：先选出被占用的 used 行，有 C(rows, used) 种；
        再给这 used 行依次分配互不相同的列，有 P(cols, used) = cols(cols-1)… 种。
        used 超过行数或列数时为 0（此时 C 或 P 的越界项不存在）。
        """
        if used < 0 or used > rows or used > cols:
            return 0
        return pascal[rows][used] * falling[cols][used] % MOD

    # 枚举上矩形（b 行 × a 列）里放 i 个车。
    # 上矩形占用的 i 列都在它的列集内，而下矩形（d 行 × (a+c) 列）的列集
    # 完整包含这个列集，所以下矩形恰好只剩 a + c - i 列可用；行互不相交，无别的耦合。
    ans = sum(
        ways(b, a, i) * ways(d, a + c - i, k - i) % MOD
        for i in range(min(a, b, k) + 1)
    )
    print(ans % MOD)


if __name__ == "__main__":
    solve()
