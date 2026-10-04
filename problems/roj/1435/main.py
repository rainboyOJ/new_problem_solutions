#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 10:12
# update_at: 2026-09-30 10:12

import sys


def peak(fs: list[tuple[int, int, int]], x: float) -> float:
    """上包络 F(x) = max(S_i(x)) 在 x 处的函数值。"""
    return max(a * x * x + b * x + c for a, b, c in fs)


def ternary_min(fs: list[tuple[int, int, int]]) -> float:
    """在 [0,1000] 上三分收缩区间，返回凸函数 F 的最小值。

    F 是一堆开口向上抛物线（含退化直线）的逐点最大值，仍是凸函数：
    每次 F(m1) < F(m2) 说明谷底只能在 [lo, m2]，否则只能在 [m1, hi]。
    100 轮后区间长 1000·(2/3)^100，远小于答案精度所需的 5e-11。
    """
    lo, hi = 0.0, 1000.0
    for _ in range(100):
        m1 = lo + (hi - lo) / 3
        m2 = hi - (hi - lo) / 3
        if peak(fs, m1) < peak(fs, m2):
            hi = m2
        else:
            lo = m1
    return peak(fs, (lo + hi) / 2)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)

    for _ in range(T):
        n = next(data)
        fs = [(next(data), next(data), next(data)) for _ in range(n)]  # n 条曲线 (a,b,c)，元组内从左到右求值
        out.append(f"{ternary_min(fs):.4f}")

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
