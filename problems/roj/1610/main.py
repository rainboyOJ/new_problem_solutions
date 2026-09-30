#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 21:43
# update_at: 2026-09-30 21:43

import sys
from collections import deque

Line = tuple[int, int]  # (斜率, 截距)：直线 y = m*x + b，公共的 x² 项统一后加


def value(line: Line, x: int) -> int:
    """直线在 x 处的取值（不含公共的 x²）。"""
    m, b = line
    return m * x + b


def is_shadow(a: Line, b: Line, c: Line) -> bool:
    """b 是否被 a、c 夹成死线：交点不前移，b 永远取不到最小值。"""
    (ma, ba), (mb, bb), (mc, bc) = a, b, c
    # 交点横坐标 (b_i - b_j) / (m_j - m_i)，斜率严格递减使分母同号，交叉相乘避免浮点
    return (bb - ba) * (mb - mc) >= (bc - bb) * (ma - mb)


def min_cost(costs: list[int], limit: int) -> int:
    """斜率优化 + 单调队列：依次推出 dp[i]，返回最后一件玩具装完的最小费用。"""
    hull: deque[Line] = deque()
    hull.append((0, 0))  # j = 0：前 0 件玩具 T=0、dp=0 对应的直线
    t = 0                # T[i] = 前缀和 S[i] + i，随 i 严格递增
    dp = 0

    for c in costs:
        t += c + 1                          # 每件玩具让前缀和与下标各 +1
        x = t - 1 - limit                   # 以 j 分段时容器长度 = x - T[j]
        while len(hull) > 1 and value(hull[0], x) >= value(hull[1], x):
            hull.popleft()                  # x 随 i 递增：被追平的首线以后只会更差
        m, b = hull[0]
        dp = m * x + b + x * x              # dp[i] = min_j 直线值 + x²
        new = (-2 * t, dp + t * t)          # dp[i] + (x - T[i])² 展开后的 (m, b)
        while len(hull) > 1 and is_shadow(hull[-2], hull[-1], new):
            hull.pop()                      # 维护下凸壳：交点左移的尾线整段多余
        hull.append(new)

    return dp


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, limit = next(data), next(data)
    costs = [next(data) for _ in range(n)]
    print(min_cost(costs, limit))


if __name__ == "__main__":
    solve()
