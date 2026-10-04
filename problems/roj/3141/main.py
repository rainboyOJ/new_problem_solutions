#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 20:08
# update_at: 2026-10-01 20:08

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    a = [next(data) for _ in range(n)]

    # f[j]：已处理的数中选出若干个、和恰好为 j 的方案数（空集对应 f[0] = 1）
    f = [0] * (m + 1)
    f[0] = 1
    for x in a:
        # 01 背包倒序枚举，保证每个数只被选一次；f[j] += f[j-x] 即“不选 x / 选 x”两种决策合并
        for j in range(m, x - 1, -1):
            f[j] += f[j - x]

    print(f[m])


if __name__ == "__main__":
    solve()
