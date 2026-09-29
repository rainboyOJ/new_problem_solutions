#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 03:43
# update_at: 2026-09-30 03:43

import sys
from itertools import batched


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    n, m = data[0], data[1]

    f = [0] * (m + 1)                              # f[v]：重量不超过 v 的最大价值
    for w, c in batched(data[2:2 + 2 * n], 2):     # 每件物品（重量，价值）
        for v in range(m, w - 1, -1):              # 倒序枚举容量，每件至多选一次
            f[v] = max(f[v], f[v - w] + c)

    print(f[m])


if __name__ == "__main__":
    solve()
