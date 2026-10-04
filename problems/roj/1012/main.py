#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 13:20
# update_at: 2026-09-29 13:20

import sys


def poly_value(x: float, a: float, b: float, c: float, d: float) -> float:
    """求三次多项式 f(x) = a x^3 + b x^2 + c x + d 的值。"""
    return a * x * x * x + b * x * x + c * x + d  # 乘加顺序与 std 一致，末位也相同


def solve() -> None:
    x, a, b, c, d = map(float, sys.stdin.buffer.read().split())  # 题面首个实数是 x
    print(f"{poly_value(x, a, b, c, d):.7f}")  # .7f 四舍五入到小数点后 7 位


if __name__ == "__main__":
    solve()
