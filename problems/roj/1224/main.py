#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 00:30
# update_at: 2026-09-30 00:30

import sys
from collections.abc import Iterable
from itertools import accumulate


def best_segment(nums: Iterable[int]) -> int:
    """一维最大非空子段和（Kadane），acc 表示"以当前元素结尾的最大和"。

    转移 max(x, acc + x)：前缀为负时从本元素重新开始，否则接在最优后缀后面。
    """
    return max(accumulate(nums, lambda acc, x: x if x > acc + x else acc + x))


def max_submatrix(rows: list[list[int]]) -> int:
    """非空子矩阵的最大元素和：枚举行区间，把列方向交给一维最大子段和。

    固定行区间 [i, j) 后每列之和是一个定值，列区间的最优选择只取决于这一维数组。
    """
    n = len(rows)
    # pref[c][t] 是第 c 列前 t 行之和，故列 c 在行区间 [i, j) 上的和 = pref[c][j] - pref[c][i]
    pref = [tuple(accumulate((0, *col))) for col in zip(*rows)]
    ans = pref[0][1]                                  # 至少取一格：用它兜住矩阵全为负数的情形
    for i in range(n):
        for j in range(i + 1, n + 1):                 # 行区间 [i, j) 保证非空
            band = (col[j] - col[i] for col in pref)  # 该行区间下每列的累加和
            ans = max(ans, best_segment(band))
    return ans


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)  # N×N 的边长
    rows = [[next(data) for _ in range(n)] for _ in range(n)]
    print(max_submatrix(rows))


if __name__ == "__main__":
    solve()
