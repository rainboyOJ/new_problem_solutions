#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 00:07
# update_at: 2026-10-01 00:07

import math
import sys

MOD = 1000  # 方程右端 g(x) 的取模常数


def count_positive_solutions(variables: int, total: int) -> int:
    """隔板法求 total 分成 variables 个正整数之和的解组数，即 C(total - 1, variables - 1)。"""
    return math.comb(total - 1, variables - 1)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    k, x = next(data), next(data)

    # 题目给定 g(x) = x^x mod 1000
    target_sum = pow(x, x, MOD)
    ans = count_positive_solutions(k, target_sum)

    print(ans)


if __name__ == "__main__":
    solve()
