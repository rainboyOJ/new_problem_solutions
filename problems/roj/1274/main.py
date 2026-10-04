#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 02:51
# update_at: 2026-09-30 02:51

import sys
from functools import cache

INF = 10 ** 18  # 比任何可能答案都大


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    a = [next(data) for _ in range(n)]

    # 前缀和：s[i] 表示前 i 堆石子总数，s[0] = 0。
    s = [0] * (n + 1)
    for i, x in enumerate(a, 1):
        s[i] = s[i - 1] + x

    @cache
    def dfs(l: int, r: int) -> int:
        """把第 l 到第 r 堆石子合并成一堆的最小得分，区间为 1-based 闭区间。"""
        if l == r:
            return 0
        return min(dfs(l, k) + dfs(k + 1, r) for k in range(l, r)) + s[r] - s[l - 1]

    print(dfs(1, n))


if __name__ == "__main__":
    solve()
