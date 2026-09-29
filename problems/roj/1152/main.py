#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 21:05
# update_at: 2026-09-29 21:05

import sys


def max3(x: int, y: int, z: int) -> int:
    """函数版求三个数的最大值：把结果作为返回值交回给调用者。"""
    top = x
    if top < y:
        top = y
    if top < z:
        top = z
    return top


def max3_proc(x: int, y: int, z: int, out: list[int]) -> None:
    """过程版求三个数的最大值：没有返回值，结果写进输出参数 out[0]。"""
    top = x
    if top < y:
        top = y
    if top < z:
        top = z
    out[0] = top


def solve() -> None:
    a, b, c = map(int, sys.stdin.read().split())

    numerator = max3(a, b, c)      # 分子 max(a, b, c)：用函数版拿返回值
    out: list[int] = [0]           # 过程版的输出参数（相当于 Pascal 的 var 参数）
    max3_proc(a + b, b, c, out)
    left = out[0]                  # 分母左因子 max(a+b, b, c)
    max3_proc(a, b, b + c, out)
    right = out[0]                 # 分母右因子 max(a, b, b+c)

    m = numerator / (left * right)
    print(f"{m:.3f}")


if __name__ == "__main__":
    solve()
