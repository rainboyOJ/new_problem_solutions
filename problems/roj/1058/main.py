#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 17:18
# update_at: 2026-09-29 17:18

import sys
from math import sqrt

DELTA_EPS = 1e-12  # 判别式落在这个范围内视为 0，用于吸收浮点误差
ZERO_EPS = 1e-6    # 根的绝对值小于它时按 0 输出，避免打印出 "-0.00000"


def no_negative_zero(x: float) -> float:
    """把 |x| < 1e-6 的根统一成 0.0：它们本来就显示为 0.00000，顺便去掉 -0.0 的负号。"""
    return 0.0 if abs(x) < ZERO_EPS else x


def solve() -> None:
    a, b, c = map(float, sys.stdin.buffer.read().split())
    delta = b * b - 4 * a * c

    if delta < -DELTA_EPS:  # 判别式显著为负：无实根
        print("No answer!")
        return
    if abs(delta) < DELTA_EPS:  # 判别式在精度内视为 0：两个相等的实根
        print(f"x1=x2={no_negative_zero(-b / (2 * a)):.5f}")
        return

    root = sqrt(delta)  # 与 C++ 的 sqrt 同为正确舍入，避免 1 ulp 级差异
    xs = sorted(((-b + root) / (2 * a), (-b - root) / (2 * a)))  # 根小者在先
    x1, x2 = map(no_negative_zero, xs)                           # 再抹掉负零的符号
    print(f"x1={x1:.5f};x2={x2:.5f}")


if __name__ == "__main__":
    solve()
