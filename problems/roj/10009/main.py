#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 17:39
# update_at: 2026-10-04 14:55

import sys
from math import gcd


def pair_gcd_counts(n: int) -> list[int]:
    """cnt[g] = 1 ≤ i, j ≤ n 中 gcd(i, j) 恰好等于 g 的数对个数。"""
    cnt = [0] * (n + 1)
    for i in range(1, n + 1):
        for j in range(1, n + 1):
            cnt[gcd(i, j)] += 1
    return cnt


def third_gcd_sum(g: int, n: int) -> int:
    """固定前两数的 gcd 为 g 时，第三个数 k 的贡献和：Σ gcd(g, k)。"""
    return sum(gcd(g, k) for k in range(1, n + 1))


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)  # 题面唯一的位置量：妹子个数 n
    cnt = pair_gcd_counts(n)

    # gcd(i, j, k) = gcd(gcd(i, j), k)：先按前两数的 gcd 分组，组内第三数的贡献相同
    ans = sum(c * third_gcd_sum(g, n) for g, c in enumerate(cnt) if c)
    print(ans)


if __name__ == "__main__":
    solve()
