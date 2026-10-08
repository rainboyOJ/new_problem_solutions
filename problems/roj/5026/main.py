#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 22:24
# update_at: 2026-10-08 22:24

import sys


def last_two_digits(n: int) -> int:
    """同余定理步步取模：与 C++ 主解同算法、同为 O(n)（不用 pow 的三分幂，见题解说明）。"""
    res = 1                      # 乘法单位元；n = 0 时输出 1，但该边界题面未定义、数据未覆盖
    for _ in range(n):
        res = res * 1992 % 100   # 中间结果恒小于 100 * 1992
    return res


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    print(last_two_digits(n))    # 按整数输出，不补前导零（n = 111 的答案文件是 "8" 而非 "08"）


if __name__ == "__main__":
    solve()
