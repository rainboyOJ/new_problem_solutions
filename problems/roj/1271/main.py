#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 02:39
# update_at: 2026-09-30 02:39

import sys

INF = 10**9  # 不可达哨兵：最大总重 1000 × 800 = 8×10^5，远小于它


def pack(dp: list[list[int]], oxygen: int, nitro: int, weight: int) -> None:
    """放入一个气缸后的 0/1 转移：dp[i][j] 表示需求量被收拢到 (i, j) 时的最小总重。

    需求是"至少"语义，状态下标按 min(i+oxygen, 上限) 收拢——超过需求的部分不再区分。
    倒序枚举下标：目标状态只落在已访问过的位置，本气缸不会被二次使用；
    而当前状态在本轮尚未被写过，读到的始终是"前 i-1 个气缸"的结果。
    """
    need_o, need_n = len(dp) - 1, len(dp[0]) - 1
    for i in range(need_o, -1, -1):
        ni = min(i + oxygen, need_o)
        row, nxt = dp[i], dp[ni]
        for j in range(need_n, -1, -1):
            cost = row[j] + weight
            nj = min(j + nitro, need_n)
            if cost < nxt[nj]:
                nxt[nj] = cost


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    need_o, need_n = next(data), next(data)  # 需要的氧气、氮气量
    k = next(data)                           # 气缸个数

    dp = [[INF] * (need_n + 1) for _ in range(need_o + 1)]
    dp[0][0] = 0  # 什么都不带时两种气体都是 0，总重 0

    for _ in range(k):
        oxygen, nitro, weight = next(data), next(data), next(data)
        pack(dp, oxygen, nitro, weight)

    print(dp[need_o][need_n])


if __name__ == "__main__":
    solve()
