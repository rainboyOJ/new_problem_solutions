#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 09:19
# update_at: 2026-10-01 09:23

import sys

INF = 1 << 60  # 不可达哨兵：远大于任何合法路径长（最多 19 * 10^7）


def set_bits(mask: int) -> list[int]:
    """列出 mask 中为 1 的点号，升序。"""
    return [k for k in range(20) if mask >> k & 1]


def hamilton_shortest(n: int, a: list[list[int]]) -> int:
    """返回从点 0 出发、不重不漏经过所有点、终点为 n-1 的最短路径长。

    状态 dp[s][j]：走过的点集为 s（一定含点 0）、终点为 j 的最短路径长。
    转移：s 的最后一个点是 j，去掉 j 后终点为 k，即 dp[s][j] = min(dp[s^1<<j][k] + a[k][j])。
    s 按数值从小到大枚举时，s ^ (1 << j) < s，保证前驱已算好。
    """
    # col[j][k] = a[k][j]：转移固定终点 j、枚举前驱 k，取的是 a 的第 j 列
    col = [[a[k][j] for k in range(n)] for j in range(n)]

    # 只枚举含点 0 的奇数集合，dp 用 mask >> 1 做下标（省一半状态）
    size = 1 << (n - 1)
    bits = [set_bits((h << 1) | 1) for h in range(size)]  # bits[h]：集合 (h<<1)|1 中的点号
    dp = [[INF] * n for _ in range(size)]
    dp[0][0] = 0  # 集合 {0}，停在起点

    for h in range(size):
        mask = (h << 1) | 1
        row = dp[h]
        # j 是"最后一个到达的点"；j = 0 时集合里只有起点、没有前驱，跳过
        for j in bits[h][1:]:
            sub = (mask ^ (1 << j)) >> 1  # 去掉点 j 后的点集（半掩码下标）
            prev = dp[sub]
            crow = col[j]
            # 前驱 k 必须在去掉 j 的集合里，取 k -> j 一步后的最小值
            row[j] = min(prev[k] + crow[k] for k in bits[sub])

    return dp[size - 1][n - 1]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    a = [[next(data) for _ in range(n)] for _ in range(n)]  # 邻接矩阵，a[i][j] = 点 i 到 j 的距离
    print(hamilton_shortest(n, a))


if __name__ == "__main__":
    solve()
