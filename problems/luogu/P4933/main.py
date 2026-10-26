#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-26 13:45
# update_at: 2026-10-26 13:45

import sys

MOD = 998244353


def count_arithmetic(heights: list[int]) -> int:
    """统计所有等差子序列(长度 1、2 也计入)。按中间项 j 分桶, 右侧查询 O(1)。"""
    n = len(heights)
    # f[i][j](i > j): 最后两项是 heights[j], heights[i] 的等差子序列个数, 含长度 2
    f = [[0] * n for _ in range(n)]
    ans = n                      # 长度 1 的子序列一定等差
    for j in range(n):
        # 固定中间项 j, 把左侧所有 f[j][k] 按高度分桶: 高度 -> 这些 f 之和
        bucket: dict[int, int] = {}
        for k in range(j):
            v = heights[k]
            bucket[v] = (bucket.get(v, 0) + f[j][k]) % MOD
        middle = heights[j]
        for i in range(j + 1, n):
            # 公差 d = heights[i] - middle, 前一项高度必须是 2*middle - heights[i]
            ways = bucket.get(2 * middle - heights[i], 0) + 1   # +1 是只取 j, i 两项
            f[i][j] = ways % MOD
            ans += ways
        ans %= MOD
    return ans % MOD


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    heights = [next(data) for _ in range(n)]
    print(count_arithmetic(heights))


if __name__ == "__main__":
    solve()
