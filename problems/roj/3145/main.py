#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 20:35
# update_at: 2026-10-01 20:49

import sys
from itertools import accumulate

INF = 1 << 60  # 只作内层取最小值的初始上界；真实代价不超过 n * 1000 * (n-1) ≈ 9e7


def min_merge_cost(stone: list[int]) -> int:
    """链上石子合并的最小总代价：区间 DP，O(n^3) 时间、O(n^2) 空间。

    f[i][j] = 把区间 [i, j] 合并成一堆的最小代价。最后一次合并必然把区间劈成
    左段 [i, k] 与右段 [k+1, j]，两段的代价 f[i][k] + f[k+1][j] 之外，
    这一次合并自身还要付 S(i, j) = ps[j+1] - ps[i]，也就是这段的质量和。
    """
    n = len(stone)
    ps = list(accumulate(stone, initial=0))  # ps[i] = 前 i 堆的质量和
    f = [[0] * n for _ in range(n)]          # 初始全 0，正好就是长度 1 的区间（不必合并）
    for length in range(2, n + 1):
        # f[i][j] 只依赖更短的区间，所以按长度从小到大递推即可保证用到的值已经算好。
        for i in range(n - length + 1):
            j = i + length - 1
            row = f[i]  # 内层是热路径，把行取到局部变量，省掉每次的 f[i] 下标查找
            best = INF
            for k in range(i, j):
                cost = row[k] + f[k + 1][j]  # 左段代价 + 右段代价，k 是最后一次合并的断点
                if cost < best:
                    best = cost
            row[j] = best + ps[j + 1] - ps[i]  # 补上最后一次合并自身的代价
    return f[0][n - 1]  # n = 1 时就是 f[0][0] = 0：只有一堆，不需要任何合并


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    stone = [next(data) for _ in range(n)]
    print(min_merge_cost(stone))


if __name__ == "__main__":
    solve()
