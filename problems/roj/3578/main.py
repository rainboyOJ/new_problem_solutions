#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 08:40
# update_at: 2026-10-02 08:40

import sys


def min_cost(pairs: list[tuple[int, int]]) -> int:
    """枚举分界点 k：前 k 颗交给 1 号系统、其余交给 2 号系统，求 r1^2 + r2^2 的最小值。"""
    n = len(pairs)

    # suf[i]：把第 i 颗及以后全交给 2 号系统所需的 r2^2，即 d2 的后缀最大值（suf[n] = 0）
    suf = [0] * (n + 1)
    for i in range(n - 1, -1, -1):
        suf[i] = max(pairs[i][1], suf[i + 1])

    # pairs 按 d1 升序：前 k 颗交给 1 号系统时 r1^2 就是第 k 颗的 d1；k = 0 表示 1 号不拦
    return min((pairs[k - 1][0] if k else 0) + suf[k] for k in range(n + 1))


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    x1, y1, x2, y2 = next(data), next(data), next(data), next(data)
    n = next(data)

    coords = [next(data) for _ in range(2 * n)]  # 之后 2N 个数：每颗导弹的 x, y 交替

    # 每颗导弹记为 (d1, d2)：到两套系统各自的距离平方
    pairs = sorted(
        ((x - x1) ** 2 + (y - y1) ** 2, (x - x2) ** 2 + (y - y2) ** 2)
        for x, y in zip(coords[::2], coords[1::2])
    )
    print(min_cost(pairs))


if __name__ == "__main__":
    solve()
