#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 04:40
# update_at: 2026-10-02 04:40

import sys
from functools import cache


@cache
def ways(n: int, k: int) -> int:
    """把 n 分成 k 份非空、不计顺序的正整数方案数（约定每份从小到大）。"""
    if n < k:  # 每份至少 1，k 份最少也要 k
        return 0
    if k == 1:  # 只剩一份，唯一分法就是 n 本身
        return 1
    # 按"是否存在等于 1 的一份"分类：
    # 有：去掉这份 1，变成 ways(n-1, k-1)；
    # 没有：每份都 ≥2，每份先扣掉 1，变成 ways(n-k, k)。
    return ways(n - 1, k - 1) + ways(n - k, k)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, k = next(data), next(data)
    print(ways(n, k))


if __name__ == "__main__":
    solve()
