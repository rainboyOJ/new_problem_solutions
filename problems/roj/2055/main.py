#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 05:19
# update_at: 2026-10-01 05:19

import sys
from collections import Counter


def solve() -> None:
    lines = sys.stdin.read().split()
    n = int(lines[0])
    grid = [lines[1 + r] for r in range(n)]

    # f[r][c] = 以 (r, c) 为右下角的最大全 1 正方形边长；
    # 全部以 k 结尾的正方形套住了以 k-1 结尾的较小正方形，按边长分桶即可。
    f = [[0] * n for _ in range(n)]
    sizes = Counter()
    for r in range(n):
        for c in range(n):
            if grid[r][c] == '1':
                top_left = f[r - 1][c - 1] if r and c else 0
                f[r][c] = min(top_left, f[r - 1][c], f[r][c - 1]) + 1
                sizes[f[r][c]] += 1

    # 边长为 k 的正方形个数 = sum(cnt[j] for j >= k)，从大到小做一次后缀和
    count = [0] * (n + 1)
    total = 0
    for k in range(n, 1, -1):
        total += sizes[k]
        if total:
            count[k] = total
    out = [f'{k} {count[k]}' for k in range(2, n + 1) if count[k]]
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
