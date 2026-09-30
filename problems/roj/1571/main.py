#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 19:01
# update_at: 2026-09-30 19:01

import sys


def min_product_sum(weight: list[int]) -> int:
    """凸多边形划分：f[i][j] = 顶点 i..j 这段子多边形的最小三角形乘积和。"""
    n = len(weight)
    f = [[0] * n for _ in range(n)]  # 相邻两点只是一条边，权值和天然为 0
    for gap in range(2, n):  # gap = j - i，至少 3 个顶点才需要划分
        for i in range(n - gap):
            j = i + gap
            # 选中间顶点 k，三角形 (i, k, j) 把子多边形劈成 [i..k]、[k..j] 两段
            f[i][j] = min(
                f[i][k] + f[k][j] + weight[i] * weight[k] * weight[j]
                for k in range(i + 1, j)
            )
    return f[0][n - 1]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)  # 顶点数
    weight = [next(data) for _ in range(n)]  # 顶点 1..N 的权值
    print(min_product_sum(weight))


if __name__ == "__main__":
    solve()
