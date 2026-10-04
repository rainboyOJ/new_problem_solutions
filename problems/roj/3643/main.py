#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 12:20
# update_at: 2026-10-02 12:20

import sys

EPS = 1e-6   # 坐标只保留两位小数，抛物线"经过"用这个精度判定
INF = 1 << 30


def line_of(pts: list[tuple[float, float]], i: int, j: int) -> int:
    """过原点与猪 i、猪 j 的抛物线顺路能打死的猪集合（bitmask）。

    i == j 时退化为"只打死 i 自己"；两点同列或开口向上（a ≥ 0）时
    不存在合法轨迹，同样只打死 i 自己。
    """
    (x1, y1), (x2, y2) = pts[i], pts[j]
    if abs(x1 - x2) < EPS:                          # 两点同列，抛物线不存在
        return 1 << i
    a = (y1 / x1 - y2 / x2) / (x1 - x2)             # 解 y=ax²+bx 过两点的方程组
    if a >= -EPS:                                   # 必须 a < 0 才能从原点射进第一象限
        return 1 << i
    b = y1 / x1 - a * x1
    return sum(1 << k for k, (x, y) in enumerate(pts) if abs(a * x * x + b * x - y) < EPS)


def solve_level(pts: list[tuple[float, float]]) -> int:
    """状压 DP：dp[已消灭的猪集合] = 最少小鸟数。"""
    n = len(pts)
    full = (1 << n) - 1
    LINE = [[line_of(pts, i, j) for j in range(n)] for i in range(n)]

    dp = [INF] * (1 << n)
    dp[0] = 0
    for mask in range(1 << n):
        rest = full ^ mask
        if dp[mask] == INF or rest == 0:            # 不可达 / 已经全灭
            continue
        low = (rest & -rest).bit_length() - 1       # 编号最小的活猪，必须由下一只鸟解决
        nxt = dp[mask] + 1
        for line in LINE[low]:
            nm = mask | line
            if nxt < dp[nm]:
                dp[nm] = nxt
    return dp[full]


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    out: list[str] = []
    T = int(next(data))

    for _ in range(T):
        n = int(next(data))
        m = next(data)  # 神秘指令类型，只提示解的结构，不影响最坏情况下的最优解
        # 依次读入 x_i、y_i（float(next) 从左到右求值，先 x 后 y）
        pts = [(float(next(data)), float(next(data))) for _ in range(n)]
        out.append(str(solve_level(pts)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
