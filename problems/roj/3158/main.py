#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 21:45
# update_at: 2026-10-01 21:45

import sys
from collections import deque
from itertools import accumulate


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    s = next(data)

    # 每个任务给出一对 (T_i, C_i)，先成对读入再分别求前缀和
    tc = [(next(data), next(data)) for _ in range(n)]
    t = [0, *accumulate(x for x, _ in tc)]  # t[i] = 前 i 个任务的时间之和
    c = [0, *accumulate(y for _, y in tc)]  # c[i] = 前 i 个任务的费用系数之和

    # f[i]：前 i 个任务全部完成的最小总费用（费用提前计算）。
    # f[i] = t[i]*(c[i]-c[j]) + s*(c[n]-c[j]) + f[j]，
    # 整理成截距形式：f[i] = t[i]*c[i] + s*c[n] + min{ f[j] - (t[i]+s)*c[j] }，
    # 花括号内即「点 (c[j], f[j]) 在斜率 k = t[i]+s 下的 y-kx 最小值」→ 下凸壳 + 单调队列。
    f = [0] * (n + 1)
    hull = deque([(0, 0)])  # 下凸壳上的点 (x, y) = (c[j], f[j])，x 随插入严格递增

    for i in range(1, n + 1):
        k = t[i] + s  # 查询斜率，随 i 单调递增

        # 队首不再最优：若到第二点的边斜率 \leqslant k，则第二点的截距更小（或相等）
        while len(hull) >= 2 and hull[1][1] - hull[0][1] <= k * (hull[1][0] - hull[0][0]):
            hull.popleft()

        best_x, best_y = hull[0]
        f[i] = best_y - k * best_x + t[i] * c[i] + s * c[n]

        # 插入新点 (c[i], f[i])：中间点落在连线上方（含共线）则破坏下凸性，弹出
        new = (c[i], f[i])
        while len(hull) >= 2 and (
            (hull[-1][1] - hull[-2][1]) * (new[0] - hull[-2][0])
            >= (new[1] - hull[-2][1]) * (hull[-1][0] - hull[-2][0])
        ):
            hull.pop()
        hull.append(new)

    print(f[n])


if __name__ == "__main__":
    solve()
