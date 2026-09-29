#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 03:03
# update_at: 2026-09-30 03:03

import sys


def max_subarray(arr: list[int]) -> int:
    """一维最大子段和：Kadane。"""
    best = cur = arr[0]
    for x in arr[1:]:
        cur = max(x, cur + x)
        best = max(best, cur)
    return best


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return
    it = iter(data)
    n = next(it)
    a = [[next(it) for _ in range(n)] for _ in range(n)]  # n x n 矩阵

    ans = a[0][0]  # 至少选一个元素
    col = [0] * n
    for top in range(n):               # 枚举子矩阵上边界
        col = [0] * n                   # 列前缀和归零
        for bottom in range(top, n):     # 枚举子矩阵下边界
            for c in range(n):
                col[c] += a[bottom][c]  # 把第 bottom 行加入每一列的累加和
            ans = max(ans, max_subarray(col))  # 当前条带内的最大子段和

    print(ans)


if __name__ == "__main__":
    solve()
