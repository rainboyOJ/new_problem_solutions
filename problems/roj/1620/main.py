#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 22:30
# update_at: 2026-09-30 22:30

import sys
from math import isqrt


def solve() -> None:
    n = int(sys.stdin.buffer.read())

    # 设 n = p*q 且 p < q，则 p ≤ √n（否则 p*q > √n*√n = n 矛盾），
    # 所以最小质因子一定落在 [2, ⌊√n⌋] 内，从小到大试除到它即可。
    # 命中的第一个 d 必是质数：若 d 是合数，它的质因子更小、早就把 n 除尽了。
    p = next(d for d in range(2, isqrt(n) + 1) if n % d == 0)
    print(n // p)  # 商就是较大的那个质数


if __name__ == "__main__":
    solve()
