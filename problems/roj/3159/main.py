#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 21:44
# update_at: 2026-10-01 21:58

import sys
from collections import deque


def push_line(hull: deque[tuple[int, int]], m: int, b: int) -> None:
    """把直线 y = m*x + b 压入下凸壳的尾部（插入斜率 m 随插入递减）。

    凸壳只保留"可能成为最小值"的直线：若队尾直线在新直线与次队尾直线的
    交点之上（三点不再构成下凸），它永远取不到最小值，直接弹掉。
    """
    while len(hull) >= 2:
        (m1, b1), (m2, b2) = hull[-2], hull[-1]
        if (b2 - b1) * (m2 - m) < (b - b2) * (m1 - m2):
            break  # 队尾仍是凸壳顶点
        hull.pop()
    hull.append((m, b))


def min_line(hull: deque[tuple[int, int]], x: int) -> int:
    """查询所有已插入直线在 x 处的最小值。

    查询点 x = 前缀时间和 + S 严格递增，所以最优直线沿凸壳单调右移，
    用队首指针（这里是 popleft）均摊 O(1) 即可，不必二分。
    """
    while len(hull) >= 2 and hull[0][0] * x + hull[0][1] >= hull[1][0] * x + hull[1][1]:
        hull.popleft()
    m, b = hull[0]
    return m * x + b


def solve() -> None:
    read = sys.stdin.buffer.readline
    n, S = int(read()), int(read())               # S 是每批任务开始前的启动时间
    times: list[int] = []                         # 第 i 个任务的执行时间 T_i
    costs: list[int] = []                         # 第 i 个任务的费用系数 C_i
    for _ in range(n):
        t, c = map(int, read().split())
        times.append(t)
        costs.append(c)
    total_c = sum(costs)

    # f[i]：前 i 个任务的最小总费用（已把启动时间折算给"它及之后所有任务"）
    # 转移展开后 f[i] = sc[i]*st[i] + S*total_c + min_j { -sc[j]*(st[i]+S) + f[j] }
    # 每个决策 j 是一条斜率 -sc[j] 递减的直线，查询点 st[i]+S 递增 → 单调队列凸壳
    hull: deque[tuple[int, int]] = deque()
    dp = st = sc = 0                              # dp = f[0] = 0
    for t, c in zip(times, costs):
        push_line(hull, -sc, dp)                  # 此刻 sc、dp 仍是第 i-1 轮的值
        st += t
        sc += c
        dp = sc * st + S * total_c + min_line(hull, st + S)
    print(dp)


if __name__ == "__main__":
    solve()
