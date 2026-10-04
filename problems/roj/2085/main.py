#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 07:46
# update_at: 2026-10-01 07:46

import sys

def max_barn_side(n: int, trees: set[tuple[int, int]]) -> int:
    """全空最大正方形的边长：dp[r][c] = 以 (r, c) 为右下角的最大空正方形边长。"""
    best = 0
    row = [0] * (n + 1)  # 上一行 dp，虚拟第 0 行全 0；第 0 列哨兵也是 0，避免 c=1 时越界
    for r in range(1, n + 1):
        cur = [0] * (n + 1)
        for c in range(1, n + 1):
            if (r, c) in trees:  # 有树：以它为右下角的正方形不存在
                cur[c] = 0
            else:
                cur[c] = min(row[c], row[c - 1], cur[c - 1]) + 1
        best = max(best, max(cur))
        row = cur
    return best


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, t = next(data), next(data)
    trees = {(next(data), next(data)) for _ in range(t)}
    print(max_barn_side(n, trees))


if __name__ == "__main__":
    solve()
