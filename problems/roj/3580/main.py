#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 08:58
# update_at: 2026-10-02 09:07

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    h = [[next(data) for _ in range(m)] for _ in range(n)]

    # cover[i][j]：格子 (i,j) 能被第 1 行哪些列的蓄水厂供到，用位集表示
    cover = [[0] * m for _ in range(n)]

    # 按海拔从高到低 DP：cover(低格) 由相邻更高格合并而来（水从高处流向低处）
    # 第 1 行格子的位集自带自己所在列，其余格子从空集开始向里并
    order = sorted(((h[i][j], i, j) for i in range(n) for j in range(m)), reverse=True)
    for height, i, j in order:
        # 第 1 行的格子自带蓄水厂，位集里永远包含自己所在的那一列
        bits = 1 << j if i == 0 else 0
        # 海拔相同的邻居互相流不通（水必须严格往低处走），只有严格更高的邻居贡献位集
        for ni, nj in ((i - 1, j), (i + 1, j), (i, j - 1), (i, j + 1)):
            if 0 <= ni < n and 0 <= nj < m and h[ni][nj] > height:
                bits |= cover[ni][nj]
        cover[i][j] = bits

    # 只要有一个第 N 行格子不可达，统计这些格子的数量后直接输出无解
    last_row = cover[n - 1]
    unreachable = sum(1 for bits in last_row if bits == 0)
    if unreachable:
        print(0)
        print(unreachable)
        return

    # 经典区间覆盖贪心：每个源点能供到的第 N 行列是一段连续区间 [lo, hi]。
    # 注意 cover[n-1][j] 是"列 j 被哪些源供到"，要转置成"每个源覆盖哪些列"。
    # 两趟扫描：正扫第一次遇到的源记左端，反扫第一次遇到的源记右端。
    lo = [0] * m
    hi = [0] * m
    seen = 0
    for j in range(m):
        fresh = last_row[j] & ~seen                 # 本列新出现的源，当前列就是它们的左端
        seen |= last_row[j]
        while fresh:
            s = (fresh & -fresh).bit_length() - 1
            fresh &= fresh - 1
            lo[s] = j
    seen = 0
    for j in range(m - 1, -1, -1):
        fresh = last_row[j] & ~seen                 # 反向扫同理得到右端
        seen |= last_row[j]
        while fresh:
            s = (fresh & -fresh).bit_length() - 1
            fresh &= fresh - 1
            hi[s] = j

    segments = sorted((lo[s], hi[s]) for s in range(m) if last_row[lo[s]] >> s & 1)
    built = 0
    reach = 0                                         # 已覆盖到列 [0, reach)
    idx = 0
    while reach < m:
        best = reach                                   # 起点不越过 reach 的区间能伸到的最远右端
        while idx < len(segments) and segments[idx][0] <= reach:
            best = max(best, segments[idx][1])
            idx += 1
        built += 1
        reach = best + 1

    print(1)
    print(built)


if __name__ == "__main__":
    solve()
