#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 18:08
# update_at: 2026-10-07 18:35

# 倍增 Floyd（min-plus 矩阵幂）+ 按位贪心。
# 只依赖标准库；n=300 时一次乘法是 3e7 次加法，纯 Python 会 TLE，
# 但算法与 C++ 同阶（没有降级成暴力），按 python-oj-short 的约定可以接受。
# 正式提交请用 main.cpp。

import sys
from operator import add

INF = 1 << 60  # 路径权值绝对值 < 511 * 1e4，用大整数当无穷，两两相加也不会溢出
BITS = 8       # 倍增层数：2^8 = 256 > n，配合按位贪心足以覆盖 0..511 条边

type Mat = list[list[int]]  # n×n 权值和矩阵，mat[i][j] = i 到 j 的最小权值和


def min_plus(a: Mat, b: Mat) -> Mat:
    """min-plus 乘法 c[i][j] = min_k a[i][k] + b[k][j]：先走 a 的一段再走 b 的一段。"""
    cols = list(zip(*b))  # 按列取，让内层能用 map(add, 行, 列) 一次算完
    half = INF // 2
    return [
        # a[i][k] = INF 配上一个负的 b[k][j] 会算出 INF + w < INF 的假路径，夹回 INF。
        # 真实路径权值绝对值远小于 INF // 2，夹不掉任何真值。
        [INF if (v := min(map(add, row, col))) > half else v for col in cols]
        for row in a
    ]


def has_negative_diag(a: Mat) -> bool:
    """主对角线出现负数，就说明存在负权闭迹，等价于存在负环。"""
    return any(a[i][i] < 0 for i in range(len(a)))


def doubled_powers(base: Mat) -> list[Mat]:
    """pw[k] = 「最多用 2^k 条边」的最小权值和；pw[0] 就是 base。"""
    pw = [base]
    for _ in range(BITS):
        pw.append(min_plus(pw[-1], pw[-1]))  # 把同一段路走两遍
    return pw


def smallest_negative_cycle(powers: list[Mat]) -> int:
    """最短负环的边数，无负环返回 0。

    按位从高位到低位定答案：cur 表示「至多 tot 条边」的最短路，
    若 cur ⊗ powers[k] 的主对角线没有负数，说明还没越过答案，这一位可以吃掉。
    """
    n = len(powers[0])
    cur = [[0 if i == j else INF for j in range(n)] for i in range(n)]  # 至多 0 条边 = 停在原地
    tot = 0
    for k in range(BITS, -1, -1):
        nxt = min_plus(cur, powers[k])
        if not has_negative_diag(nxt):
            cur, tot = nxt, tot + (1 << k)
    return tot + 1 if has_negative_diag(min_plus(cur, powers[0])) else 0


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    # base = pw[0]：最多用 1 条边（对角线为 0，表示「停在原地」）
    base = [[0 if i == j else INF for j in range(n)] for i in range(n)]
    for _ in range(m):
        u, v, w = next(data), next(data), next(data)
        base[u - 1][v - 1] = w  # 题面保证无重边

    print(smallest_negative_cycle(doubled_powers(base)))


if __name__ == "__main__":
    solve()
