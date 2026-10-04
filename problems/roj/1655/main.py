#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 00:25
# update_at: 2026-10-01 00:25

import sys
from math import comb

MAX_SIDE = 1000  # 题面 m、n 的上界，欧拉函数表按它建一次


def totients(limit: int) -> list[int]:
    """phi[1..limit]：phi[t] 是不超过 t 且与 t 互质的正整数个数（埃氏筛）。"""
    phi = list(range(limit + 1))
    for p in range(2, limit + 1):
        if phi[p] == p:                             # p 没被更小的质数除过，说明 p 是质数
            for k in range(p, limit + 1, p):
                phi[k] -= phi[k] // p
    return phi


def pairs_divisible_by(total: int, step: int) -> int:
    """[0, total] 上的有序点对 (x1, x2)，满足 x1 < x2 且 x2 − x1 能被 step 整除。

    距离取 k·step（k ≥ 1）时左端点有 total − k·step + 1 种，对 k 求和即得。
    """
    cnt = total // step                             # 距离最大到 cnt·step，k 只遍历 1..cnt
    return cnt * (total + 1) - step * cnt * (cnt + 1) // 2


PHI = totients(MAX_SIDE)  # 主流程只查表，不在求和里现算欧拉函数


def count_triangles(m: int, n: int) -> int:
    """(m+1)×(n+1) 个格点中，三点不共线的取法数 = 全部三点组 − 共线三点组。"""
    rows, cols = m + 1, n + 1                       # 两个方向的格点数
    limit = min(m, n)                               # 位移分量超过它，另一个方向就放不下第二个点

    # step_x[t] 是横坐标差能被 t 整除的点对数（下标即步长，开头的 0 占位，步长从 1 起）。
    # 横纵独立，两者相乘正是"横纵位移都被 t 整除、且以这对点为端点"的线段条数。
    step_x = [0] + [pairs_divisible_by(m, step) for step in range(1, limit + 1)]
    step_y = [0] + [pairs_divisible_by(n, step) for step in range(1, limit + 1)]

    # 位移 (dx, dy) 的最大公约数为 g 时，线段中间恰好夹着 g − 1 个格点，也就是以这两点
    # 为端点的共线三点组数。由 Σ_{t | g} φ(t) = g 得 g − 1 = Σ_{t | g, t ≥ 2} φ(t)：
    # 交换求和次序后，第 t 层要数的正是"dx、dy 都能被 t 整除"的线段，于是斜线段总数
    # 写成按 φ(t) 的加权和。g 最大只到 min(m, n)，t 也只需枚举到这里。
    weighted = sum(PHI[t] * step_x[t] * step_y[t] for t in range(1, limit + 1))
    slanted = 2 * (weighted - step_x[1] * step_y[1])    # 扣掉 t = 1 层，权重才变成 g − 1

    # 水平共线：每条水平格线（cols 个点）任取 3 个；垂直同理
    axis_aligned = rows * comb(cols, 3) + cols * comb(rows, 3)

    return comb(rows * cols, 3) - axis_aligned - slanted


def solve() -> None:
    m, n = map(int, sys.stdin.buffer.read().split())
    print(count_triangles(m, n))


if __name__ == "__main__":
    solve()
