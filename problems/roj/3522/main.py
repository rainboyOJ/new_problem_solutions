#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 05:19
# update_at: 2026-10-02 05:19

import sys

NEG = -(10**100)  # dp_max 的哨兵：比任何可能的乘积都小（权值 ≤ 9，乘积 ≤ 9^50）
INF = 10**100     # dp_min 的哨兵


def best_products(n: int, pre: list[int], m: int) -> tuple[int, int]:
    """链 b[0..n-1]（pre 为其前缀和）分成 m 段的（最小乘积, 最大乘积）。"""
    # dp_min[i][j]：前 i 个数分成 j 段的最小乘积；dp_max 同理取最大。
    dp_min = [[0] * (m + 1) for _ in range(n + 1)]
    dp_max = [[0] * (m + 1) for _ in range(n + 1)]
    for i in range(n + 1):
        dp_min[i][0] = 1 if i == 0 else INF       # 分 0 段只有前 0 个数合法（乘积单位元 1）
        dp_max[i][0] = 1 if i == 0 else NEG
    for i in range(1, n + 1):
        for j in range(1, min(i, m) + 1):
            # 枚举第 j 段的终点 i：第 j 段是 a[k+1..i]，权值 = 段和 mod 10，乘积本身不取模
            candidates_min = [
                dp_min[k][j - 1] * ((pre[i] - pre[k]) % 10)
                for k in range(j - 1, i)
                if dp_min[k][j - 1] < INF         # 跳过不合法的哨兵状态
            ]
            candidates_max = [
                dp_max[k][j - 1] * ((pre[i] - pre[k]) % 10)
                for k in range(j - 1, i)
                if dp_max[k][j - 1] > NEG // 2
            ]
            dp_min[i][j] = min(candidates_min) if candidates_min else INF
            dp_max[i][j] = max(candidates_max) if candidates_max else NEG
    return dp_min[n][m], dp_max[n][m]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)  # 圆桌上的整数个数
    m = next(data)  # 要分成的段数
    a = [next(data) for _ in range(n)]

    # 环 → 链：把数组复制一份接在后面，枚举每个起点 st，取 a[st..st+n-1] 这条链。
    b = a + a
    pre = [0]
    for x in b:
        pre.append(pre[-1] + x)  # pre[i] - pre[k] = b[k..i-1] 的段和

    ans_min = INF
    ans_max = NEG
    for st in range(n):
        lo, hi = best_products(n, pre[st : st + n + 1], m)
        ans_min = min(ans_min, lo)
        ans_max = max(ans_max, hi)
    print(ans_min)
    print(ans_max)


if __name__ == "__main__":
    solve()
