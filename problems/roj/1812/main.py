#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 06:12
# update_at: 2026-10-08 06:12

import sys
from functools import cache
from math import gcd

MOD = 10 ** 9  # 题面模数，非质数，组合数不能用逆元


@cache
def comb(n: int, k: int) -> int:
    """C(n,k) mod 1e9：模数非质数，用杨辉递推而不是费马小定理。"""
    if k < 0 or k > n:
        return 0
    return 1 if k == 0 else (comb(n - 1, k - 1) + comb(n - 1, k)) % MOD


def count_direction(a: int, b: int, n: int, w: int, h: int, d2: int) -> int:
    """本原方向 (a,b) 贡献的方案数（不含斜率正负对称的 2 倍）。

    直线上的格点按 (a,b) 等距排开，首末点指标跨度为 M 时，把 M 拆成 N-1 段、
    每段至少 k 得 C(M-(N-1)k+N-2, N-2) 种，再乘首点的 (W+1-M*a)*(H+1-M*b) 种位置。
    """
    s2 = a * a + b * b  # 方向向量长度的平方
    k = 1
    while k * k * s2 < d2:  # 整数判定最小步长，避开 sqrt 的浮点误差
        k += 1
    base = (n - 1) * k  # 跨度 M 的下界：N-1 段每段至少 k

    if a == 0:
        max_m = h // b  # 纯竖直方向，只受 y 跨度限制
    elif b == 0:
        max_m = w // a  # 纯水平方向，只受 x 跨度限制
    else:
        max_m = min(w // a, h // b)

    return sum(
        comb(m - base + n - 2, n - 2) * (w + 1 - m * a) * (h + 1 - m * b)
        for m in range(base, max_m + 1)
    ) % MOD


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)
    for _ in range(T):
        n, w, h, d = next(data), next(data), next(data), next(data)
        if n == 1:  # 只选一个点：任取一个格点
            out.append(str((w + 1) * (h + 1) % MOD))
            continue
        d2, span = d * d, n - 1
        ans = count_direction(1, 0, n, w, h, d2) + count_direction(0, 1, n, w, h, d2)
        # 斜向要有解必须 M >= span 且 M*a <= w、M*b <= h，故 a <= w//span、b <= h//span
        ans += 2 * sum(
            count_direction(a, b, n, w, h, d2)
            for a in range(1, w // span + 1)
            for b in range(1, h // span + 1)
            if gcd(a, b) == 1  # 只取本原方向，避免同一斜率重复计数
        )
        out.append(str(ans % MOD))
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
