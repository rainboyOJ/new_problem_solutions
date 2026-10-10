#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 20:34
# update_at: 2026-10-07 20:34

import sys

MOD = 20170927  # 题面要求的模数

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Tree = list[int]          # 树状数组：只维护「Σx² / Σy² / Σx·y」里的某一个分量
type Vel = list[tuple[int, int]]  # 每个电子当前的速度 (x, y)


def add(tree: Tree, pos: int, val: int) -> None:
    """树状数组单点加：把 val（已归一到 [0, MOD)）加到下标 pos 上。"""
    size = len(tree) - 1
    while pos <= size:
        tree[pos] = (tree[pos] + val) % MOD
        pos += pos & -pos


def prefix(tree: Tree, pos: int) -> int:
    """树状数组前缀和：前 pos 个电子的该分量之和（对 MOD 取模）。"""
    total = 0
    while pos > 0:
        total += tree[pos]
        pos -= pos & -pos
    return total % MOD


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    # 三个分量各开一棵树状数组，下标 1..n；vel 记录速度以便算单点增量
    sums = [[0] * (n + 1) for _ in range(3)]  # 依次为 Σx²、Σy²、Σx·y
    ta, tb, tc = sums
    vel: Vel = [None] * (n + 1)

    for i in range(1, n + 1):
        x, y = next(data) % MOD, next(data) % MOD
        vel[i] = (x, y)
        add(ta, i, x * x % MOD)
        add(tb, i, y * y % MOD)
        add(tc, i, x * y % MOD)

    out: list[str] = []
    for _ in range(m):
        op = next(data)
        if op == 1:
            p, x, y = next(data), next(data) % MOD, next(data) % MOD
            ox, oy = vel[p]
            # 单点改速度：三个分量各自只有一处变化，增量先归一到 [0, MOD)
            add(ta, p, (x * x - ox * ox) % MOD)
            add(tb, p, (y * y - oy * oy) % MOD)
            add(tc, p, (x * y - ox * oy) % MOD)
            vel[p] = (x, y)
        else:
            l, r = next(data), next(data)
            # 区间和 = 前缀和相减；三个分量分别是 Σx²、Σy²、Σx·y
            px = (prefix(ta, r) - prefix(ta, l - 1)) % MOD
            py = (prefix(tb, r) - prefix(tb, l - 1)) % MOD
            pr = (prefix(tc, r) - prefix(tc, l - 1)) % MOD
            # Σ_{i<j} (x_i·y_j − x_j·y_i)² = (Σx²)(Σy²) − (Σx·y)²
            ans = (px * py - pr * pr) % MOD
            out.append(ans)

    if out:
        sys.stdout.write("\n".join(map(str, out)) + "\n")


if __name__ == "__main__":
    solve()
