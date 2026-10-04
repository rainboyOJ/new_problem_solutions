#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 23:15
# update_at: 2026-09-29 23:15

import sys

MOD = 32767  # 题面给定的模数


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    T = next(data)
    ks = [next(data) for _ in range(T)]  # 所有询问的 k，先读入再一起回答

    # Pell 数列前 max(ks) 项整体取模：递推只涉及加法和乘法，模运算下保持一致
    limit = max(ks)
    pell = [0] * (limit + 1)
    pell[1] = 1 % MOD
    if limit >= 2:
        pell[2] = 2 % MOD
    for i in range(3, limit + 1):
        pell[i] = (2 * pell[i - 1] + pell[i - 2]) % MOD

    print('\n'.join(str(pell[k]) for k in ks))


if __name__ == "__main__":
    solve()
