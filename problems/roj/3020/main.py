#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 10:25
# update_at: 2026-10-01 10:25

import sys


def solve() -> None:
    data = list(map(int, sys.stdin.read().split()))
    if not data:
        return
    n = data[0]
    a0, b0 = data[1], data[2]
    # 每个大臣按 a * b 升序排序
    ministers = sorted(
        [(data[i], data[i + 1]) for i in range(3, 3 + 2 * n, 2)],
        key=lambda m: m[0] * m[1],
    )

    prefix_prod = a0
    ans = 0
    for a, b in ministers:
        ans = max(ans, prefix_prod // b)
        prefix_prod *= a

    print(ans)


if __name__ == "__main__":
    solve()
