#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-04-18 10:00
# update_at: 2026-04-18 10:00

import sys


def count_subsets(n: int, target: int) -> int:
    """计算从 1 到 n 中选取若干互不相同的数使其和为 target 的方案数。"""
    dp = [0] * (target + 1)
    dp[0] = 1
    for num in range(1, n + 1):
        for s in range(target, num - 1, -1):
            dp[s] += dp[s - num]
    return dp[target]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    try:
        n = next(data)
    except StopIteration:
        return
    total_sum = n * (n + 1) // 2

    # 和为奇数无法二等分；否则每个无序二划分对应含/不含某个元素的有序方案数的一半
    if total_sum % 2 != 0:
        print(0)
        return

    target = total_sum // 2
    ans = count_subsets(n, target) // 2
    print(ans)


if __name__ == "__main__":
    solve()
