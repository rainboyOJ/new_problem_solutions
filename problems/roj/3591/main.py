#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 09:27
# update_at: 2026-10-02 09:27

import sys
from math import comb

MOD = 10007  # 题面要求的模数


def solve() -> None:
    a, b, k, n, m = map(int, sys.stdin.read().split())

    # (ax+by)^k 中 x^n y^m 的系数 = C(k,n) * a^n * b^m
    # k ≤ 1000，comb 直接精确计算；a^n b^m 用内置快速幂取模
    ans = comb(k, n) * pow(a, n, MOD) * pow(b, m, MOD) % MOD
    print(ans)


if __name__ == "__main__":
    solve()
