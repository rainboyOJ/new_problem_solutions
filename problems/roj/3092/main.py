#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 16:28
# update_at: 2026-10-01 16:30

import sys
from math import comb

MOD = 10007  # 系数要对 10007 取模；它是素数，且 k ≤ 1000 < 10007·10007


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    a, b, k, n, m = (next(data) for _ in range(5))

    # 展开 (ax+by)^k 时每项都形如「k 个括号各挑一个字母」：想让 x 出现 n 次，
    # 就必须恰好有 n 个括号挑 ax，选法 C(k,n) 种；剩下 m = k-n 个括号只能挑 by。
    # 还要给每个 ax 带上因子 a、每个 by 带上因子 b，于是这一项的系数是
    # C(k,n)·a^n·b^m；m 是自由的，但取值由 n 定死，不必再乘第二个组合数。
    binom = comb(k, n) % MOD  # math.comb 给精确整数，n ≤ 1000 直接算，不必用 Lucas
    print(binom * pow(a, n, MOD) * pow(b, m, MOD) % MOD)


if __name__ == "__main__":
    solve()
