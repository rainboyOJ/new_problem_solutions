#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 21:15
# update_at: 2026-09-29 21:15

import math

EPS = 1e-6  # 最后一项绝对值小于该阈值就停止累加


def arctanx(x: float) -> float:
    """交错级数求 arctan(x)：逐项累加，直到下一项绝对值 < EPS。"""
    term = x  # 当前项 x^(2k+1)，由上一项乘 -x^2 递推
    total = 0.0
    for i in range(1, 10**9, 2):
        if abs(term / i) < EPS:  # 该项已小于阈值，成为"最后一项"，不再累加
            break
        total += term / i
        term *= -x * x  # 分子乘 -x² 得到下一项
    return total


def solve() -> None:
    print(f"{6 * arctanx(1 / math.sqrt(3)):.10f}")


if __name__ == "__main__":
    solve()
