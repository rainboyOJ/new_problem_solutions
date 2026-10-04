#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 10:25
# update_at: 2026-10-01 10:25

import sys


def solve() -> None:
    tokens = sys.stdin.buffer.read().split()
    if not tokens:
        return
    data = iter(map(int, tokens))
    n = next(data)            # 大臣人数
    a0, b0 = next(data), next(data)  # 国王的左、右手
    # 每个大臣按 a * b 升序排序
    ministers = sorted(
        [(next(data), next(data)) for _ in range(n)],
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
