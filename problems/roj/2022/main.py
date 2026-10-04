#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 03:19
# update_at: 2026-10-01 03:19

import sys
from math import gcd


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    # 枚举所有 (分子, 分母)，gcd 归约去重；0 只保留 0/1，避免 0/2..0/n 混进来。
    # tuple 直接比较是先比分子的，必须按分数值 a/b 排序。
    fracs = sorted(
        {(a // gcd(a, b), b // gcd(a, b)) for b in range(1, n + 1) for a in range(b + 1)},
        key=lambda t: t[0] / t[1],
    )
    sys.stdout.write(''.join(f'{a}/{b}\n' for a, b in fracs))


if __name__ == "__main__":
    solve()
