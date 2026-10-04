#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 22:40
# update_at: 2026-09-30 22:40

import sys
from collections import deque


def hull_add(hull: deque, slope: int, intercept: int) -> None:
    """把直线 y = slope*x + intercept 并入下凸壳（直线按斜率递减顺序入队）。

    若「尾前直线与尾直线」的交点不小于「尾直线与新直线」的交点，尾直线
    在所有位置都被新直线压住，出队。交点横坐标之比用交叉相乘判断，避免除法。
    """
    while len(hull) >= 2:
        m1, c1 = hull[-2]
        m2, c2 = hull[-1]
        # 交点 x(l1,l2) = (c2-c1)/(m1-m2)，两条分母都为正，可直接交叉相乘
        if (c2 - c1) * (m2 - slope) >= (intercept - c2) * (m1 - m2):
            hull.pop()
        else:
            break
    hull.append((slope, intercept))


def hull_query(hull: deque, x: int) -> int:
    """查询凸壳在横坐标 x 处的最小值：查询点单调不减，最优直线只向队尾移动。"""
    while len(hull) >= 2 and hull[0][0] * x + hull[0][1] >= hull[1][0] * x + hull[1][1]:
        hull.popleft()
    return hull[0][0] * x + hull[0][1]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    # sw[i] = 前 i 棵树总重量；swd[i] = 前 i 棵树的 Σ w_k·pos_k；
    # f[i] = 两个新锯木厂中较高的在树 j<i、较低的建在树 i 时，树 1..i 的最小运费
    sw: list[int] = [0] * (n + 1)
    swd: list[int] = [0] * (n + 1)
    f: list[int] = [0] * (n + 1)

    hull: deque = deque()  # 直线 y = -sw[j]·x + sw[j]·pos_j，斜率随 j 递减
    pos = 0                # 当前树到山顶的距离 pos_i，山顶处 pos_1 = 0
    for i in range(1, n + 1):
        w, d = next(data), next(data)
        sw[i], swd[i] = sw[i - 1] + w, swd[i - 1] + w * pos

        # f[i] = sw[i]·pos_i - swd[i] + min_j ( sw[j]·pos_j - sw[j]·pos_i )
        # min 部分恰是候选直线族在 x = pos_i 处的最小值，用凸壳 O(1) 取到
        if i > 1:
            f[i] = sw[i] * pos - swd[i] + hull_query(hull, pos)

        hull_add(hull, -sw[i], sw[i] * pos)  # 树 i 成为「较高锯木厂」的候选
        pos += d                             # 推进到下一棵树，读完 d_n 后即山脚

    # 第二个锯木厂在树 i 时，树 i+1..n 全部运到山脚锯木厂的费用
    tail = [(sw[n] - sw[i]) * pos - (swd[n] - swd[i]) for i in range(n + 1)]
    print(min(f[i] + tail[i] for i in range(2, n + 1)))


if __name__ == "__main__":
    solve()
