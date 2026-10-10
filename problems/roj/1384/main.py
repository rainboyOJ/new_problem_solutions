#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 16:15
# update_at: 2026-10-08 16:15

import sys

MAXN = 105          # 珍珠数上限 99，矩阵开到 105 留余量

# reach[i][j] 为 True 表示确定珍珠 i 比珍珠 j 重（含传递推出的关系）
type ReachMatrix = list[list[bool]]


def transitive_closure(reach: ReachMatrix, n: int) -> None:
    """原地求传递闭包：若 i 比 k 重且 k 比 j 重，则确定 i 比 j 重。"""
    for k in range(1, n + 1):
        row_k = reach[k]
        for i in range(1, n + 1):
            if reach[i][k]:
                reach[i] = [a or b for a, b in zip(reach[i], row_k)]


def count_not_middle(reach: ReachMatrix, n: int) -> int:
    """统计不可能是中位数的珍珠数：确定偏重或偏轻的数量超过 n/2 就不可能是中间那颗。"""
    half = n // 2  # n 为奇数，中位数必须恰好有 n/2 颗比它重的珍珠
    total = 0
    for i in range(1, n + 1):
        heavier = sum(reach[j][i] for j in range(1, n + 1))  # 确定比 i 重的珍珠数
        lighter = sum(reach[i][1 : n + 1])                   # 确定比 i 轻的珍珠数
        if heavier > half or lighter > half:
            total += 1
    return total


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    reach: ReachMatrix = [[False] * MAXN for _ in range(MAXN)]
    for _ in range(m):
        x, y = next(data), next(data)
        reach[x][y] = True

    transitive_closure(reach, n)
    print(count_not_middle(reach, n))


if __name__ == "__main__":
    solve()
