#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys


def max_energy(n: int, a: list[int]) -> int:
    """计算环形项链合并所能释放的最大总能量。

    破环成链：将长度为 n 的标记序列复制一份变为 2n。
    dp[l][r] 表示将区间珠子 [l, r] 完全合并成一颗珠子所释放的最大能量。
    合并后的新珠子头标记为 a[l]，尾标记为 a[r+1]。
    枚举最后一次合并的位置 k (l <= k < r)：
    左半部分合并成珠子 (a[l], a[k+1])，右半部分合并成珠子 (a[k+1], a[r+1])，
    最后合并释放 a[l] * a[k+1] * a[r+1]。
    """
    head = a + a
    dp = [[0] * (2 * n) for _ in range(2 * n)]

    for length in range(2, n + 1):
        for l in range(2 * n - length):
            r = l + length - 1
            dp[l][r] = max(
                dp[l][k] + dp[k + 1][r] + head[l] * head[k + 1] * head[r + 1]
                for k in range(l, r)
            )

    return max(dp[i][i + n - 1] for i in range(n))


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    a = [next(data) for _ in range(n)]
    print(max_energy(n, a))


if __name__ == "__main__":
    solve()
